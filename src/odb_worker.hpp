#ifndef ODB_WORKER_HPP
#define ODB_WORKER_HPP
#include "odb_stat.hpp"
#include "odb_headers.hpp"
#include <sstream>
#include <queue>
#include <mutex>
#include <vector>
#include <functional>
#include <chrono>
#include <thread>
#include <cstddef>
#include <limits>
#include <exception.hpp>
#include <unistd.h>

#define  MAX_CONNECT_RETRY 3600
#define  MAX_POOL_SIZE  100
#define  MAX_COMMIT_TIMEOUT  60
#define  MAX_COMMIT_COUNT  10000
#define  MAX_QUE_SIZE  (std::numeric_limits<int>::max())


namespace oi
{
    struct odb_worker_param
    {
        int max_que_size;
        int pool_size;
        int commit_count;
        int commit_timeout; // second
        odb_worker_param();
        std::string to_string()const;
    };
    std::ostream operator<<(std::ostream& os, const odb_worker_param& prm);

    class odb_worker_base
    {
        public:
            enum class state {NEW, READY, TERMINATED};
        protected:
            volatile state _state;
            odb_worker_param _init_param;
            oi_database * _db;

            oi::semaphore _sem;
            std::mutex    _que_gurad;

            std::vector<std::thread*> _worker_threads;
            std::function<void(oi::exception)> _exception_handler;

            odb_stat      _stat;
            std::mutex    _stat_gurad;
            
        private:
            odb_worker_base(const odb_worker_base&);//is PRIVATE to avoid pass by value - no body_base
            odb_worker_base& operator=(const odb_worker_base&); //is PRIVATE to avoid assigning - no body
        public:
            odb_worker_base();
            void init(oi_database* db, 
                    const odb_worker_param& prm,
                    std::function<void(oi::exception)>  handler
                    ) throw(oi::exception);
            virtual void worker() = 0;
            virtual odb_stat get_stat()throw();
            void finalize()throw();
            virtual ~odb_worker_base();

    };

    template<class T>
        class odb_worker: public odb_worker_base
    {
        private:
            std::queue<T*> _que;
            void worker()
            {
                
             //   T obj;
                T* p = NULL;
                std::vector<T*> uncommited;
                bool wait_res = false;
                execution_state exec_state = execution_state::SUCCESS;
                odb::core::transaction* trans = NULL;
                try
                {
                    trans = new odb::core::transaction(_db->begin());
                    int commit_counter = 0;
                    uint64_t diff_time = 0;

                    auto last_commit = std::chrono::high_resolution_clock::now();
                    while(_state == state::READY)
                    {
                        wait_res = _sem.wait_for(100);
                        if(_state != state::READY)
                        {
                            break;
                        }
                        if(wait_res == false)
                        {

                            auto nw = std::chrono::high_resolution_clock::now(); 
                            if(std::chrono::duration_cast<std::chrono::seconds>(nw - last_commit).count() >= _init_param.commit_timeout )
                            {
                                trans->commit();
                                typename std::vector<T*>::iterator it;
                                for(it= uncommited.begin(); it != uncommited.end(); it++)
                                {
                                    delete *it;
                                }
                                uncommited.clear();
                                trans->reset(_db->begin());
                                commit_counter = 0;
                                last_commit = nw;
                            }

                            continue;
                        }
                        _que_gurad.lock();
                        {
                            p = _que.front();
                            _que.pop();
                        }
                        _que_gurad.unlock();
                        uncommited.push_back(p);
                        try
                        {
                            auto start = std::chrono::high_resolution_clock::now(); 
                            _db->persist(*p);

                            commit_counter++;
                            if(commit_counter > _init_param.commit_count
                                    || 
                                    std::chrono::duration_cast<std::chrono::seconds>(start - last_commit).count() > _init_param.commit_timeout )
                            {
                                trans->commit();
                                typename std::vector<T*>::iterator it;
                                for(it= uncommited.begin(); it != uncommited.end(); it++)
                                {
                                    delete *it;
                                }
                                uncommited.clear();
                                trans->reset(_db->begin());
                                commit_counter = 0;
                                last_commit = start;
                            }
                            auto end = std::chrono::high_resolution_clock::now(); 

                            diff_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                            exec_state = execution_state::SUCCESS;
                        }
                        catch(const odb::recoverable & e)
                        {
                            int retry_count =0;
                            while(retry_count < MAX_CONNECT_RETRY)
                            {
                                try
                                {
                                    delete trans;
                                    trans = new odb::core::transaction(_db->begin());
                                    break;
                                }
                                catch(...){
                                }
                                sleep(1);
                                retry_count++;
                            }
                            if(retry_count >= MAX_CONNECT_RETRY)
                            {
                                oi::exception ox(__FILE__, __FUNCTION__, " maximum no of connection retries exceeded (type: %)", typeid(T).name());
                                _exception_handler(ox ); 
                                continue;
                            }
                            typename std::vector<T*>::iterator it;
                            _que_gurad.lock();
                            {
                                for(it= uncommited.begin(); it != uncommited.end(); it++)
                                {
                                    _que.push(*it);
                                    _sem.notify();
                                }
                                uncommited.clear();
                            }
                            _que_gurad.unlock();
                            exec_state = execution_state::RECOVERED;
                            diff_time = 0;
                        }
                        catch(const odb::exception& ex)
                        {
                            oi::exception ox("odb", "exception", ex.what());
                            ox.add_msg(__FILE__, __FUNCTION__, "unhandled odb exception on type %", typeid(T).name());
                            exec_state = execution_state::FAILED;
                            diff_time = 0;
                            _exception_handler(ox);

                        }
                        _stat_gurad.lock();
                        {
                            _stat.update(diff_time, exec_state);
                        }
                        _stat_gurad.unlock();
                    }
                    try
                    {
                        trans->commit();
                    }
                    catch(const odb::exception& ex)
                    {
                        oi::exception ox(__FILE__, __FUNCTION__, "odb exception on type `%': %" ,typeid(T).name(), ex.what() );
                        _exception_handler(ox);
                    }
                }
                catch(std::exception & ex)
                {
                    oi::exception ox(__FILE__, __FUNCTION__, "worker thread on type % terminated due to std::exception: %", typeid(T).name(), ex.what());
                    _exception_handler(ox);
                }
                catch(...)
                {
                    oi::exception ox(__FILE__, __FUNCTION__, "worker thread on type % terminated due to an unknown exception", typeid(T).name());
                    _exception_handler(ox);
                }
            }

        public:
            odb_stat get_stat()throw()
            {
                
                odb_stat temp = odb_worker_base::get_stat();
                _que_gurad.lock();
                {
                    temp.set_que_len(_que.size());
                }
                _que_gurad.unlock();
                return temp;
            }
            void persist(const T & obj)throw(oi::exception)
            {
                
                if(_state != state::READY)
                {
                    throw oi::exception(__FILE__, __FUNCTION__, "invalid use of un-initilized/finalized worker");
                }
                _que_gurad.lock();
                {
                    if(static_cast<int>(_que.size()) >= _init_param.max_que_size)
                    {
                        _que_gurad.unlock();
                        throw oi::exception(__FILE__, __FUNCTION__, (std::string("maximum queue size exceeded! max limit is ") + std::to_string(_init_param.max_que_size)).c_str());
                    }
                    T * p = new T(obj);
                    _que.push(p);
                }
                _que_gurad.unlock();
                _sem.notify();
            }

    };


}
#endif
