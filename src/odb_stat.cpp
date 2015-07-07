#include "odb_stat.hpp"
namespace oi {
std::ostream& operator<<(std::ostream& os, const odb_stat& od) {
    os << "fail: " << od._fail_count
       << "que len: " << od._que_len
       << "success: {";
    os << operator<<(os, static_cast<stat_info>(od));
    os << "}";
    return os;
}

odb_stat::odb_stat():stat_info() {
    _que_len    = 0;
    _fail_count = 0;
    _is_active = false;
}

int  odb_stat::get_que_len()const {
    return _que_len;
}

int  odb_stat::get_fail_count() const{
    return _fail_count;
}

void odb_stat::set_que_len(size_t len) {
    _que_len = static_cast<int>(len);
}

void odb_stat::update(uint64_t val, bool success) {
    if(_is_active)
    {
        if(success) {
            set(val);
        }
        else {
            _fail_count++;
        }
    }
}

void odb_stat::reset() {
    _is_active = true;
    _que_len = 0;
    _fail_count = 0;
    stat_info::reset();
}
}
