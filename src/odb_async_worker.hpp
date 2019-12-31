#ifndef ODB_ASYNC_WORKER_HPP
#define ODB_ASYNC_WORKER_HPP
#include "odb_worker.hpp"

namespace oi {

class odb_async_worker {
    public:
        odb_async_worker();
        odb_async_worker(const odb_async_worker&) = delete;
        odb_async_worker& operator=(const odb_async_worker&) = delete;
        void init(oi_database* db, const odb_worker_param& prm, std::function<void(oi::exception)>  handler );
        odb_stat get_stat() noexcept;
        std::map<std::string,odb_stat> get_detailed_stat() noexcept;

        template<typename T>
        void set_local_handler(std::function<void(oi::exception, const T& obj)> handler,
                               std::function<void(const T& obj)> post_callback = nullptr) {
            if(_state != odb_worker_base::state::READY) {
                throw oi::exception(__FILE__, __FUNCTION__, "Invalid use of un-initilized/finalized worker");
            }
            std::string t_name = typeid(T).name();
            std::map<std::string, odb_worker_base*>::iterator it;
            odb_worker<T>* wr = nullptr;
            {
                std::lock_guard<std::mutex> m(_workers_guard);
                it = _workers.find(t_name);
                if(it == _workers.end()) {
                    wr = new odb_worker<T>();
                    wr->init(_db, _init_param, handler, _exception_handler, post_callback);
                    _workers[t_name] = static_cast<odb_worker_base*>(wr);
                }
                else {
                    throw oi::exception(__FILE__, __FUNCTION__,
                                        "Unable to recreate channel! this method should be "
                                        "called before any"" `persist' invokation");
                }
            }
        }
        template<typename T>
        void persist(const T& obj) {
            if(_state != odb_worker_base::state::READY) {
                throw oi::exception(__FILE__, __FUNCTION__, "Invalid use of un-initilized/finalized worker");
            }
            std::string t_name = typeid(T).name();
            std::map<std::string, odb_worker_base*>::iterator it;
            odb_worker<T>* wr = nullptr;
            {
                std::lock_guard<std::mutex> m(_workers_guard);
                it = _workers.find(t_name);
                if(it == _workers.end()) {
                    wr = new odb_worker<T>();
                    wr->init(_db, _init_param, _exception_handler);
                    _workers[t_name] = static_cast<odb_worker_base*>(wr);
                }
                else {
                    wr = static_cast<odb_worker<T>*>(it->second);
                }
            }
            wr->persist(obj);
        }

        void finalize() noexcept;
    private:
        odb_worker_base::state _state;
        std::map<std::string, odb_worker_base*> _workers;
        std::mutex _workers_guard;
        odb_worker_param _init_param;
        oi_database* _db;
        std::function<void(oi::exception)> _exception_handler;
};
}

#endif

