#ifndef ODB_STAT_HPP
#define ODB_STAT_HPP
#include<common.hpp>
#include<iostream>
namespace oi {
    enum class execution_state{SUCCESS = 0, RECOVERED = 1, FAILED =2 };
class odb_stat: public stat_info {
    friend std::ostream& operator<<(std::ostream& os, const odb_stat& od);
  private:
    bool _is_active;
    int _que_len;
    int _failure_count;
    int _recover_count;
  public:
    void reset();
    void set_que_len(size_t len);
    void update(uint64_t val, execution_state st);
    odb_stat();
    int get_que_len()const;
    int get_fail_count()const;
    int get_recover_count()const;
};

std::ostream& operator<<(std::ostream& os, const odb_stat& od);

}
#endif
