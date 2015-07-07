#include "odb_worker.hpp"
namespace oi
{
    odb_worker_param::odb_worker_param()
    {
        max_que_size = 0;
        pool_size = 0;
        commit_timeout = 0;
        commit_count = 0;
    }
    std::string odb_worker_param::to_string()const
    {
        std::stringstream sstr;
        sstr << "max_que_size: " << max_que_size
            << "pool_size: " << pool_size
            << "commit_count: " << commit_count
            << "commit_timeout: " << commit_timeout;
        return sstr.str();
    }

}
