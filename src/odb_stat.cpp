#include "odb_stat.hpp"
namespace oi {
std::ostream& operator<<(std::ostream& os, const odb_stat& od) {
    os << " fail: " << od._failure_count
       << " recover attempts: " << od._recover_count
       << " que len: " << od._que_len
       << " success: {";
    os << static_cast<stat_info>(od);
    os << "}";
    return os;
}

odb_stat::odb_stat():stat_info() {
    _que_len    = 0;
    _failure_count = 0;
    _recover_count = 0;
    _is_active = false;
}
odb_stat::odb_stat(const stat_info& st):stat_info(st)
{
    _que_len    = 0;
    _failure_count = 0;
    _recover_count = 0;
    _is_active = false;
}

odb_stat odb_stat::operator+(const odb_stat & od)
{
    odb_stat os(stat_info::operator+(static_cast<stat_info>(od)));
    os._que_len = _que_len + od._que_len;
    os._failure_count = _failure_count  + od._failure_count ;
    os._recover_count = _recover_count  + od._recover_count ;
    return os; 
}

int  odb_stat::get_que_len()const {
    return _que_len;
}

int  odb_stat::get_fail_count() const{
    return _failure_count;
}

int  odb_stat::get_recover_count() const
{
    return _recover_count;
}

void odb_stat::set_que_len(size_t len) {
    _que_len = static_cast<int>(len);
}

void odb_stat::update(uint64_t val, execution_state st) {
    if(_is_active)
    {
        switch(st)
        {
            case execution_state::SUCCESS:
                set(val);
                break;
            case execution_state::RECOVERING:
                _recover_count++;
                break;
            case execution_state::FAILED:
                _failure_count++;
                break;
        };
    }
}

void odb_stat::reset() {
    _is_active = true;
    _que_len = 0;
    _failure_count = 0;
    _recover_count = 0;
    stat_info::reset();
}
}
