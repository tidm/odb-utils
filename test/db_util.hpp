#ifndef __OI_SYS_DB_UTILS
#define __OI_SYS_DB_UTILS
#include<odb/core.hxx>
#include "../src/odb_headers.hpp"
class sys_db_util {
    private:
        oi_database* db_sys;
    public:
        sys_db_util();
        ~sys_db_util();
        void init(const std::string& sys_user,const std::string& pass,const std::string& db);
        std::string create_user(const std::string& quota);
        void drop_user(const std::string&);
        void alter_user(const std::string& user, bool set_lock, std::string quota);

};
#endif
