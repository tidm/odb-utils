#include "odb_worker.hpp"
#include <fmt/format.h>

oi::odb_worker_param::odb_worker_param():
    max_que_size{0},
    pool_size{0},
    commit_count{0},
    commit_timeout{0},
    blocking_mode{true},
    drop_failed{false} {
}

std::string oi::odb_worker_param::to_string() const {
    return fmt::format("max_que_size: {},\n"
                       "pool_size: {},\n"
                       "commit_count: {},\n"
                       "commit_timeout: {},\n"
                       "blocking_mode: {}"
                       ,max_que_size
                       ,pool_size
                       ,commit_count
                       ,commit_timeout
                       ,(blocking_mode ? "true": "false"));
}

oi::odb_worker_base::odb_worker_base():
    _state{state::NEW},
    _db{nullptr} {
}

void oi::odb_worker_base::init(oi_database* db,
                               const odb_worker_param& prm,
                               std::function<void(oi::exception)> handler) {
    if(_state != state::NEW) {
        throw oi::exception(__FILE__, __FUNCTION__,
                            "Invalid odb_worker_base state (re-initialization or initialization of a finalized worker)");
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
                            "invalid initialization parameter: {}\n"
                            "  0 < pool_size < {}\n"
                            "  0 < commit_count < {}\n"
                            "  0 < commit_timeout < {}\n"
                            "  exception_handler != null",
                            prm.to_string(),
                            MAX_POOL_SIZE,
                            MAX_COMMIT_COUNT,
                            MAX_COMMIT_TIMEOUT);
    }
    _exception_handler  = handler;
    _init_param = prm;
    if(_init_param.blocking_mode) {
        _sem_full.set_init_size(_init_param.max_que_size);
    }
    _db = db;
    _state = state::READY;
    for(int i=0; i< _init_param.pool_size; i++) {
        _worker_threads.emplace_back(&odb_worker_base::worker, this);
    }
}

oi::odb_stat oi::odb_worker_base::get_stat() noexcept {
    odb_stat temp;
    std::lock_guard<std::mutex> m(_stat_gurad);
    temp = _stat;
    _stat.reset();
    return temp;
}

void oi::odb_worker_base::finalize() noexcept {
    if(_state == state::READY) {
        _state = state::TERMINATED;
        for(auto& th: _worker_threads) {
            th.join();
        }
    }
    _state = state::TERMINATED;
}
