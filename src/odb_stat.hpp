#ifndef ODB_STAT_HPP
#define ODB_STAT_HPP
#include<common.hpp>
#include<iostream>
namespace oi {
class odb_stat: public stat_info {
    friend std::ostream& operator<<(std::ostream& os, const odb_stat& od);
  private:
    bool _is_active;
    int _que_len;
    int _fail_count;
  public:
    void reset();
    void set_que_len(size_t len);
    void update(uint64_t val, bool success);
    odb_stat();
    int get_que_len()const;
    int get_fail_count()const;
};

std::ostream& operator<<(std::ostream& os, const odb_stat& od);

}
#endif
