#include "req_agent.hpp"
#include "req_agent_odb.hpp"
#include "../src/odb_worker.hpp"
oi::odb_worker<ns2__reg_agent_obj>  worker;
void ex_handler(oi::exception ex, ns2__reg_agent_obj obj)
{
    std::cerr << ex.what() << std::endl;
   // throw ex;
}
bool finished;
void get_stat()
{
    oi::odb_stat st;
    st = worker.get_stat();
    while(finished == false || st.get_que_len() > 0)
    {
        st = worker.get_stat();
        std::cerr << "\n========================\n" << st << std::endl;
        sleep(1);
    }
}
int main()
{
    finished = false;
    oi_database * db;
    db  = new oi_database("OI_TESTING", "ot", "10.0.0.111:1521/orcl");

    oi::odb_worker_param prm;
    prm.max_que_size = 3000000;
    prm.pool_size = 2;
    prm.commit_count = 100;
    prm.commit_timeout = 1;

    std::function<void(oi::exception, const ns2__reg_agent_obj&)> f= & ex_handler;
    worker.init(db, prm, f);

    ns2__reg_agent_obj  reg_obj;

    reg_obj.tx_type = std::rand() % 10000;//
    reg_obj.hypertag_id = 3;//
    reg_obj.bank_code = 4;//
    reg_obj.agent_code =std::to_string(std::rand() % 66660618);//
    reg_obj.cif_id =  std::rand() % 1006;
    reg_obj.acc_id = "7";
    reg_obj.acc_type = 8;
    reg_obj.net_operator= "9";
    reg_obj.phone = 10;
    reg_obj.home_currency = 11;
    reg_obj.home_country = "12";
    reg_obj.home_province = "13";
    reg_obj.home_region = "14";
    reg_obj.home_city = "15";
    reg_obj.home_township = "16";
    reg_obj.date_birth = "17";
    reg_obj.id_type = std::rand() % 10618;
    reg_obj.id_no = "19";
    reg_obj.gender = "20";
    reg_obj.occupation = 21;
    reg_obj.home_branch = "22";
    reg_obj.service_plan = "23";
    reg_obj.signup_loc = "24";
    reg_obj.signup_date = "25";
    reg_obj.magent_code = "26";
    reg_obj.funder_acct_id = "27";

    std::thread th(&get_stat);
    for(int i=0; i< 500000; i++)
    {
        reg_obj.tx_id = reg_obj.tx_id++ ;
        worker.persist(reg_obj);
    }
    finished = true;
    th.join();
    worker.finalize();
    return 0;
}
