#include "req_agent.hpp"
#include "req_agent_odb.hpp"
#include "../src/odb_async_worker.hpp"
#include <unistd.h>
#include <fstream>
#include <string_formatter.hpp>
#include "db_util.hpp"
oi::odb_async_worker  worker;
sys_db_util sysutil;
oi_database* db_sys;
std::string user;
void ex_handler(oi::exception ex) {
    std::cerr << "#### generic handler" << std::endl;
    std::cerr << ex.what() << std::endl;
    throw ex;
}
void alter_user(){
        try{
            sysutil.alter_user(user, false, "unlimited"); 
        }catch(std::exception& ex){
            std::cerr << "ALTER ERR:" <<  ex.what() << std::endl;
        }
}
void local_handler(oi::exception ex, const ns2__reg_agent_obj& obj) {
    static int i =0;
    i++;
    if(i==1000){
        std::thread th(alter_user);
        th.join();
    }
    std::cerr << "**** local handler" << std::endl;
    std::cerr << ex.what() << std::endl;
    //std::cerr << obj << std::endl;
    throw ex;
}
bool finished;
void get_stat() {
    oi::odb_stat st;
    st = worker.get_stat();
    while(finished == false || st.get_que_len() > 0) {
        st = worker.get_stat();
        std::cerr << "\n========================\n" << st << std::endl;
        sleep(1);
    }
}
int main() {
    int trans_count = 50000;
    finished = false;
    sysutil.init("SYSTEM", "oiadmin1391", "10.0.0.166:1521/oi");

    user = sysutil.create_user("500K");
    oi_database* db;
    db  = new oi_database(user, "1233", "10.0.0.166:1521/oi");
    {
        odb::transaction t1 (db->begin ());
        db->execute(" CREATE TABLE \"ns2__reg_agent_obj\" ( \
            \"tx_id\" NUMBER(20) NOT NULL, \
                \"tx_type\" NUMBER(5) NOT NULL, \
                \"hypertag_id\" NUMBER(20) NOT NULL, \
                \"bank_code\" NUMBER(10) NOT NULL, \
                \"agent_code\" VARCHAR2(512) NULL, \
                \"cif_id\" NUMBER(20) NOT NULL, \
                \"acc_id\" VARCHAR2(512) NULL, \
                \"acc_type\" NUMBER(3) NOT NULL, \
                \"net_operator\" VARCHAR2(512) NULL)");
        t1.commit();
    }
    std::cerr << "table created" << std::endl;
    int cnt = 0;
    try{
        oi::odb_worker_param prm;
        prm.max_que_size = 100;
        prm.pool_size = 10;
        prm.commit_count = 10;
        prm.commit_timeout = 1;
        prm.blocking_mode = true;
        prm.drop_failed = false;
        std::function<void(oi::exception)> f= & ex_handler;
        std::function<void(oi::exception, const ns2__reg_agent_obj&)> f2= &local_handler;
        worker.init(db, prm, f);
        worker.set_local_handler<ns2__reg_agent_obj>(f2);
        ns2__reg_agent_obj  reg_obj;
        reg_obj.tx_type = std::rand() % 10000;//
        reg_obj.hypertag_id = 30;//
        reg_obj.bank_code = 4;//
        reg_obj.agent_code =std::to_string(std::rand() % 66660618)+"22222222222222222222222222222222222222";//
        reg_obj.cif_id =  std::rand() % 1006;
        reg_obj.acc_id = "700000";
        reg_obj.acc_type = 8;
        reg_obj.net_operator= "9";
        std::thread th(&get_stat);
        for(int i=0; i< trans_count; i++) {
            reg_obj.tx_id = i;
            worker.persist<ns2__reg_agent_obj>(reg_obj);
        }
        std::cerr << "putting on the que finished.waiting..." << std::endl;
        std::cerr << "finalizing..." << std::endl;
        worker.finalize();
        std::cerr << "finalized" << std::endl;
        std::cerr << "waiting for status thread..." << std::endl;
        finished = true;
        th.join();
        odb::transaction t (db->begin ());
        std::unique_ptr<count_reg_agent> rq (db->query_one<count_reg_agent> ());
        cnt = rq->cnt;
        t.commit();
        delete db;
    }catch(std::exception& ex){
        sysutil.drop_user(user);
        throw ex;
    }
    sysutil.drop_user(user);
    if(cnt != trans_count) {
        std::cerr << "trans_count: " << trans_count << " table includes: " << cnt << std::endl;
        exit(-1);
    }
    else {
        std::cerr << "SUCCEEDED !trans_count: " << trans_count << " table includes: " << cnt << std::endl;
    }
    return 0;
}
