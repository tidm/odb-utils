#include "db_util.hpp"
#include <iostream>
sys_db_util::sys_db_util() {
    db_sys = nullptr;
}
sys_db_util::~sys_db_util() {
    delete db_sys;
}
void sys_db_util::init(const std::string& sys_user,const std::string& pass,const std::string& db) {
    db_sys  = new oi_database(sys_user, pass, db);
}
std::string sys_db_util::create_user(const std::string& quota) {
    srand(time(NULL));
    std::string user = std::string( "OI_TMP" + std::to_string(std::abs(rand()%10000)));
    odb::transaction t0 (db_sys->begin ());
    db_sys->execute(std::string("create user ") + user + " identified by 1233 default tablespace USERS quota "+ quota +" on USERS");
    db_sys->execute("grant connect,create table to " + user );
    t0.commit();
    std::cerr << "user " << user << " created and required permissions granted"  << std::endl;
    return user;
}
void sys_db_util::drop_user(const std::string& user) {
    odb::transaction t0(db_sys->begin ());
    db_sys->execute(std::string("drop user ") + user + " cascade");
    t0.commit();
    std::cerr << "user " << user << " dropped"  << std::endl;
}
void sys_db_util::alter_user(const std::string& user, bool lock, std::string quota) {
    odb::transaction t0(db_sys->begin ());
    std::string sqlstr = std::string("alter user ") + user + " quota " + quota + " on  USERS account " + (lock? " lock": "unlock" );
    std::cerr << "ALTER " << sqlstr << std::endl;
    db_sys->execute(sqlstr);
    t0.commit();
    std::cerr << "user " << user << " altered"  << std::endl;
}
