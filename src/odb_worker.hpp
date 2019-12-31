// TODO: Needs cleanup

#ifndef ODB_WORKER_HPP
#define ODB_WORKER_HPP

#include "odb_stat.hpp"
#include "odb_headers.hpp"
#include <cstddef>
#include <deque>
#include <mutex>
#include <atomic>
#include <vector>
#include <functional>
#include <chrono>
#include <thread>
#include <iostream>
#include <exception.hpp>

#define  MAX_POOL_SIZE  100
#define  MAX_COMMIT_TIMEOUT  60
#define  MAX_COMMIT_COUNT  10000
#define  MAX_QUE_SIZE  100000000

namespace oi {
struct odb_worker_param {
    odb_worker_param();
    std::string to_string() const;
    std::size_t max_que_size;
    int pool_size;
    int commit_count;
    // TODO: Must be of type std::chrono::seconds
    int commit_timeout; // second
    bool blocking_mode;
    bool drop_failed;
};
std::ostream operator<<(std::ostream& os, const odb_worker_param& prm);

class odb_worker_base {
    public:
        enum class state : uint8_t {NEW, READY, TERMINATED};
    protected:
        // TODO: is state able to be atomic?
        std::atomic<state> _state;
        odb_worker_param _init_param;
        oi_database* _db;

        oi::semaphore _sem;
        oi::semaphore _sem_full;
        std::mutex    _que_gurad;

        std::vector<std::thread> _worker_threads;
        std::function<void(oi::exception)> _exception_handler;

        odb_stat      _stat;
        std::mutex    _stat_gurad;

    private:
        odb_worker_base(const odb_worker_base&);//is PRIVATE to avoid pass by value - no body_base
        odb_worker_base& operator=(const odb_worker_base&); //is PRIVATE to avoid assigning - no body
    public:
        odb_worker_base();
        virtual ~odb_worker_base() = default;
        virtual void init(oi_database* db,
                          const odb_worker_param& prm,
                          std::function<void(oi::exception)>  handler
                         );
        virtual void worker() = 0;
        virtual odb_stat get_stat() noexcept;
        void finalize() noexcept;

};

template<class T>
class odb_worker: public odb_worker_base {
    public:
        std::function<void(oi::exception, const T& obj)> _local_exception_handler;
        std::function<void(const T&)>  _post_handler;

        void init(oi_database* db,
                  const odb_worker_param& prm,
                  std::function<void(oi::exception)>  handler
                 ) {
            odb_worker_base::init(db, prm, handler);
        }


        void init(oi_database* db,
                  const odb_worker_param& prm,
                  std::function<void(oi::exception, const T& obj)>  local_handler,
                  std::function<void(oi::exception)>  handler,
                  std::function<void(const T&)> post_handler

                 ) {
            _init_param = prm;
            _local_exception_handler  = local_handler;
            _post_handler = post_handler;
            //           _state = state::READY;
            //            for(int i=0; i< _init_param.pool_size; i++) {
            //                _worker_threads.emplace_back(&odb_worker_base::worker, this);
            //            }
            odb_worker_base::init(db, prm, handler);
        }


        odb_stat get_stat() noexcept {
            if(_state != odb_worker_base::state::READY) {
                return odb_stat();
            }
            odb_stat temp = odb_worker_base::get_stat();
            {
                std::lock_guard<std::mutex> m{_que_gurad};
                temp.set_que_len(_que.size());
            }
            return temp;
        }
        void persist(const T& obj) {
            if(_state != state::READY) {
                throw oi::exception(__FILE__, __FUNCTION__, "invalid use of un-initilized/finalized worker");
            }
            if(_init_param.blocking_mode) {
                _sem_full.wait();
            }
            std::unique_lock<std::mutex> lck{_que_gurad};
            if(_que.size() >= _init_param.max_que_size ) {
                throw oi::exception(__FILE__, __FUNCTION__,
                                    (std::string("maximum queue size exceeded! max limit is ") + std::to_string(
                                         _init_param.max_que_size)).c_str());
            }
            T* p = new T(obj);
            _que.push_back(p);
            lck.unlock();
            _sem.notify();
        }
    private:
        std::deque<T*> _que;
        bool reconnect(odb::core::transaction*& trans ) {
            std::size_t q_size = 0;
            while(true)  {
                std::cerr << "RECONNENCTING..." << std::endl;
                std::unique_lock<std::mutex> m{_que_gurad};
                q_size = _que.size();
                m.unlock();
                if(_state != state::READY && q_size == 0) {
                    break;
                }
                try {
                    std::unique_lock<std::mutex> guard{_stat_gurad};
                    _stat.update(0, execution_state::RECOVERING);
                    guard.unlock();
                    if(trans != nullptr) {
                        delete trans;
                    }
                    trans = nullptr;
                    trans = new odb::core::transaction(_db->begin());
                    break;
                }
                catch(...) {
                    std::cerr << "UNABLE TO RECOOENECT" << std::endl;
                    trans = nullptr;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            if(_state != state::READY && q_size == 0) {
                return false ;
            }
            else {
                return true;
            }
        }

        void do_persist(T* p) {
            auto start = std::chrono::steady_clock::now();
            _db->persist(*p);
            auto end = std::chrono::steady_clock::now();
            uint64_t diff_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::lock_guard<std::mutex> guard{_stat_gurad};
            _stat.update(diff_time, execution_state::SUCCESS);
        }

        bool do_commit(std::chrono::high_resolution_clock::time_point& last_commit,
                       int& commit_counter,
                       odb::core::transaction*& trans,
                       std::vector<T*>& uncommited) {
            // TODO: API mush changed to use steady clock instead. Leaving unchanged for the sake of BC
            auto nw = std::chrono::high_resolution_clock::now();
            auto time_to_last_commit = std::chrono::duration_cast<std::chrono::seconds>(nw - last_commit).count();
            bool r  = true;
            if(time_to_last_commit >= _init_param.commit_timeout || commit_counter >= _init_param.commit_count ) {
                try {
                    trans->commit();
                    for(auto i: uncommited) {
                        if(_init_param.blocking_mode) {
                            _sem_full.notify();
                        }
                        if(i != nullptr) {
                            delete i;
                        }
                    }
                    uncommited.clear();
                    commit_counter = 0;
                    last_commit = nw;
                    trans->reset(_db->begin());
                }
                catch(odb::exception& ox) {
                    r = reconnect(trans);
                }
            }
            return r;
        }

        void worker() {
            //   T obj;
            T* p = nullptr;
            T p2;
            std::vector<T*> uncommited;
            bool wait_res = false;
            odb::core::transaction* trans = nullptr;
            try {
                trans = new odb::core::transaction(_db->begin());
                int commit_counter = 0;
                auto last_commit = std::chrono::high_resolution_clock::now();
                auto last_shrink = std::chrono::high_resolution_clock::now();
                bool persisted = true;
                //start of main LOOP
                while(true) {
                    // TODO: 100 what? use std::chrono API instead
                    wait_res = _sem.wait_for(100);
                    if(_state != state::READY and wait_res == false) {//someone has called finalize()
                        break;
                    }
                    //check if a commit command should be executed
                    bool r = do_commit(last_commit, commit_counter, trans, uncommited);
                    if(!r) {
                        break;
                    }
                    if(wait_res == false) {//there is no new object to store
                        continue;
                    }
                    auto nw = std::chrono::high_resolution_clock::now();
                    auto time_to_last_shrink = std::chrono::duration_cast<std::chrono::seconds>(nw - last_shrink).count();
                    //poping an object from the Q
                    std::unique_lock<std::mutex> m{_que_gurad};
                    p = _que.front();
                    p2 = *p;
                    _que.pop_front();
                    //shrink the q to release memory
                    if(time_to_last_shrink >= _init_param.commit_timeout) {
                        _que.shrink_to_fit();
                        last_shrink = std::chrono::high_resolution_clock::now();
                    }
                    m.unlock();
                    uncommited.push_back(p);
                    try {
                        do_persist(p);
                        p2 =*p;
                        ++commit_counter;
                    }
                    catch(const odb::exception& e) {
                        persisted = false;
                        oi::exception ox("odb", "exception" , e.what());
                        ox.add_msg(__FILE__, __FUNCTION__, " unable to persist type: % ", typeid(T).name());
                        try {
                            if(_local_exception_handler && p != nullptr) {
                                _local_exception_handler(ox, *p);
                            }
                            else {
                                _exception_handler(ox );
                            }
                        }
                        catch(...) {}
                        bool r = reconnect(trans);
                        if(!r) {
                            break;
                        }
                        if(_init_param.drop_failed) {
                            if(_init_param.blocking_mode) {
                                _sem_full.notify();
                            }
                            std::cerr << "DROPPED" << std::endl;
                            if(p != nullptr) {
                                delete p;
                            }
                            p = nullptr;
                            if(uncommited.size() > 0) {
                                uncommited.pop_back();
                            }
                        }
                        {
                            std::lock_guard<std::mutex> m{_stat_gurad};
                            _stat.update(0, execution_state::FAILED);
                        }
                        for(const auto& i : uncommited) {
                            std::unique_lock<std::mutex> m{_que_gurad};
                            _que.push_back(i);
                            _sem.notify();
                            m.unlock();
                        }
                        uncommited.clear();
                    }
                    r = do_commit(last_commit, commit_counter, trans, uncommited);
                    if(!r) {
                        break;
                    }
                    if(_post_handler && persisted ) {
                        try {
                            _post_handler(p2);
                        }
                        catch(...) {
                        }
                    }
                }
                try {
                    trans->commit();
                }
                catch(const odb::exception& ex) {
                    oi::exception ox(__FILE__, __FUNCTION__, "odb exception on type `%': %" ,typeid(T).name(), ex.what() );
                    if(_local_exception_handler && p != nullptr) {
                        _local_exception_handler(ox, *p);
                    }
                    else {
                        _exception_handler(ox );
                    }
                }
            }
            catch(std::exception& ex) {
                oi::exception ox(__FILE__, __FUNCTION__, "worker thread on type % terminated due to std::exception: %",
                                 typeid(T).name(), ex.what());
                if(_local_exception_handler && p != nullptr) {
                    _local_exception_handler(ox, *p );
                }
                else {
                    _exception_handler(ox );
                }
            }
            catch(...) {
                oi::exception ox(__FILE__, __FUNCTION__, "worker thread on type % terminated due to an unknown exception",
                                 typeid(T).name());
                if(_local_exception_handler && p != nullptr) {
                    _local_exception_handler(ox,*p  );
                }
                else {
                    _exception_handler(ox );
                }
            }
        }
};

}
#endif
