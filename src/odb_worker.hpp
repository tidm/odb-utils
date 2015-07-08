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

    template<class T>
        class odb_worker
        {
            enum class state {NEW, READY, TERMINATED};
            private:
            volatile state _state;
            odb_worker_param _init_param;
            oi_database * _db;

            oi::semaphore _sem;
            std::queue<T> _que;
            std::mutex    _que_gurad;

            std::vector<std::thread*> _worker_threads;
            std::function<void(oi::exception, const T& data)> _exception_handler;

            odb_stat      _stat;
            std::mutex    _stat_gurad;
            private:
            odb_worker(const odb_worker&);//is PRIVATE to avoid pass by value - no body
            odb_worker& operator=(const odb_worker&); //is PRIVATE to avoid assigning - no body
            void worker()
            {
                T obj;
                bool wait_res = false;
                try
                {
                    odb::core::transaction t(_db->begin());
                    int commit_counter = 0;

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
                            continue;
                        }
                        _que_gurad.lock();
                        {
                            obj = _que.front();
                            _que.pop();
                        }
                        _que_gurad.unlock();
                        try
                        {
                            auto start = std::chrono::high_resolution_clock::now(); 
                            _db->persist(obj);

                            commit_counter++;
                            if(commit_counter > _init_param.commit_count
                                    || 
                                    std::chrono::duration_cast<std::chrono::seconds>(start - last_commit).count() > _init_param.commit_timeout )
                            {
                                t.commit();
                                t.reset(_db->begin());
                                commit_counter = 0;
                                last_commit = start;
                            }
                            auto end = std::chrono::high_resolution_clock::now(); 

                            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                            _stat_gurad.lock();
                            {
                                _stat.update( diff , true);
                            }
                            _stat_gurad.unlock();
                        }
                        catch(const odb::exception& ex)
                        {
                            oi::exception ox(__FILE__, __FUNCTION__, (std::string("odb exception ") + ex.what()).c_str());
                            _stat_gurad.lock();
                            {
                                _stat.update(0, false);
                            }
                            _stat_gurad.unlock();
                            _exception_handler(ox, obj);
                        }
                    }
                    try
                    {
                        t.commit();
                    }
                    catch(const odb::exception& ex)
                    {
                        oi::exception ox(__FILE__, __FUNCTION__, (std::string("odb exception") + ex.what()).c_str());
                        _exception_handler(ox, obj);
                    }
                }
                catch(std::exception & ex)
                {
                    oi::exception ox(__FILE__, __FUNCTION__, (std::string("worker thread terminated due to std::exception: ") + ex.what()).c_str());
                    _exception_handler(ox, obj);
                }
                catch(...)
                {
                    oi::exception ox(__FILE__, __FUNCTION__, "worker thread terminated due to an unknown exception");
                    _exception_handler(ox, obj);
                }
            }

            public:
            odb_worker()
            {
                _state= state::NEW;
                _db = nullptr;
            }
            void init(oi_database* db, 
                    const odb_worker_param& prm,
                    std::function<void(oi::exception, const T& data)>  handler
                    ) throw(oi::exception)
            {
                if(_state != state::NEW)
                {
                    throw oi::exception(__FILE__, __FUNCTION__, 
                            "invalid odb_worker state(re-initialization or initialization of a finalized worker)");
                }
                if(db == nullptr)
                {
                    throw oi::exception(__FILE__, __FUNCTION__, "database pointer is null");
                }
                if( prm.pool_size <= 0 || 
                        prm.commit_count <= 0 || 
                        prm.commit_timeout <= 0 || 
                        prm.max_que_size <= 0 ||
                        prm.pool_size > MAX_POOL_SIZE ||
                        prm.max_que_size> MAX_QUE_SIZE ||
                        prm.commit_timeout > MAX_COMMIT_TIMEOUT ||
                        handler == nullptr
                  )
                {
                    std::stringstream sstr;
                    sstr << "invalid initialization parameter: " << prm.to_string().c_str()
                        << "  0 <= pool_size < " << MAX_POOL_SIZE
                        << "  0 <= commit_count < " << MAX_COMMIT_COUNT
                        << "  0 <= commit_timeout < " << MAX_COMMIT_TIMEOUT
                        << "  exception_handler != null ";
                    throw oi::exception(__FILE__, __FUNCTION__, sstr.str().c_str());
                }
                _exception_handler  = handler;
                _init_param = prm;
                _db = db;
                _state = state::READY;
                for(int i=0; i< _init_param.pool_size; i++)
                {
                    _worker_threads.push_back(new std::thread(std::bind(&odb_worker::worker, this)));
                }
            }
            void persist(const T & obj)throw(oi::exception)
            {
                if(_state != state::READY)
                {
                    throw oi::exception(__FILE__, __FUNCTION__, "invalid use of un-initilized/finalized worker");
                }
                _que_gurad.lock();
                {
                    if(_que.size() >= _init_param.max_que_size)
                    {
                        _que_gurad.unlock();
                        throw oi::exception(__FILE__, __FUNCTION__, (std::string("maximum queue size exceeded! max limit is ") + std::to_string(_init_param.max_que_size)).c_str());
                    }
                    _que.push(obj);
                }
                _que_gurad.unlock();
                _sem.notify();
            }
            odb_stat get_stat()throw()
            {
                odb_stat temp;
                _stat_gurad.lock();
                {
                    temp = _stat;
                    _stat.reset();
                }
                _stat_gurad.unlock();

                _que_gurad.lock();
                {
                    temp.set_que_len(_que.size());
                }
                _que_gurad.unlock();
                return temp;
            }
            void finalize()throw()
            {
                if(_state == state::READY)
                {
                    _state = state::TERMINATED;
                    for(int i=0; i< _init_param.pool_size; i++)
                    {
                        _worker_threads[i]->join();
                        delete _worker_threads[i];
                    }
                }
                _state = state::TERMINATED;
            }
            ~odb_worker()
            {

            }

        };
}
#endif
