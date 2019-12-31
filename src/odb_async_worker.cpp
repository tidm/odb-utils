#include "odb_async_worker.hpp"

oi::odb_async_worker::odb_async_worker():
    _state{odb_worker_base::state::NEW},
    _db{nullptr} {
}

void oi::odb_async_worker::init(oi_database* db,
                                const odb_worker_param& prm,
                                std::function<void(oi::exception)>  handler) {
    if(_state != odb_worker_base::state::NEW) {
        throw oi::exception(__FILE__, __FUNCTION__,
                            "invalid state(re-initialization or initialization of a finalized worker)");
    }
    if(db == nullptr) {
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
      ) {
        throw oi::exception(__FILE__, __FUNCTION__,
                            "Invalid initialization parameter: {}\n"
                            "0 <= pool_size < {}\n"
                            "0 <= commit_count < {}\n"
                            "0 <= commit_timeout < {}\n"
                            "exception_handler != null\n"
                            ,prm.to_string()
                            ,MAX_POOL_SIZE
                            ,MAX_COMMIT_COUNT
                            ,MAX_COMMIT_TIMEOUT);
    }
    _exception_handler = handler;
    _init_param = prm;
    _db = db;
    _state = odb_worker_base::state::READY;
}

oi::odb_stat oi::odb_async_worker::get_stat() noexcept {
    if(_state != odb_worker_base::state::READY) {
        return odb_stat();
    }
    std::map<std::string, odb_worker_base*>::iterator it;
    odb_stat st, aggr_st;
    if(_state == odb_worker_base::state::READY) {
        {
            std::lock_guard<std::mutex> m(_workers_guard);
            for( it = _workers.begin(); it != _workers.end(); it++) {
                st = it->second->get_stat();
                aggr_st = aggr_st + st;
            }
        }
    }
    return aggr_st;
}

std::map<std::string, oi::odb_stat> oi::odb_async_worker::get_detailed_stat() noexcept {
    if(_state != odb_worker_base::state::READY) {
        return std::map<std::string,odb_stat>();
    }
    std::map<std::string, odb_worker_base*>::iterator it;
    std::map<std::string,odb_stat> st;
    if(_state == odb_worker_base::state::READY) {
        std::lock_guard<std::mutex> m(_workers_guard);
        for( it = _workers.begin(); it != _workers.end(); it++) {
            st[it->first] = it->second->get_stat();
        }
    }
    return st;
}

void oi::odb_async_worker::finalize() noexcept {
    if(_state == odb_worker_base::state::READY) {
        std::map<std::string, odb_worker_base*>::iterator it;
        {
            std::lock_guard<std::mutex> m(_workers_guard);
            for( it = _workers.begin(); it != _workers.end(); it++) {
                it->second->finalize();
                delete it->second;
            }
        }
    }
    _state = odb_worker_base::state::TERMINATED;
}
