#include "req_agent.hpp"
#include "req_agent_odb.hpp"
#include "../src/odb_worker.hpp"
std::ostream& operator<<(std::ostream & os, const ns2__reg_agent_obj & obj)
{

    //os << " tx_id " << obj.tx_id ;
    //os << " tx_type " << obj.tx_type ;
    //os << " hypertag_id " << obj.hypertag_id ;
    //os << " bank_code " << obj.bank_code ;
    //os << " agent_code " << obj.agent_code ;
    //os << " cif_id " << obj.cif_id ;
    //os << " acc_id " << obj.acc_id ;
    //os << " acc_type " << obj.acc_type ;
    //os << " net_operator " << obj.net_operator ;
    //os << " phone " << obj.phone ;
    //os << " home_currency " << obj.home_currency ;
    //os << " home_country " << obj.home_country ;
    //os << " home_province " << obj.home_province ;
    //os << " home_region " << obj.home_region ;
    //os << " home_city " << obj.home_city ;
    //os << " home_township " << obj.home_township ;
    //os << " date_birth " << obj.date_birth ;
    //os << " id_type " << obj.id_type ;
    //os << " id_no " << obj.id_no ;
    //os << " gender " << obj.gender ;
    //os << " occupation " << obj.occupation ;
    //os << " home_branch " << obj.home_branch ;
    //os << " service_plan " << obj.service_plan ;
    //os << " signup_loc " << obj.signup_loc ;
    //os << " signup_date " << obj.signup_date ;
    //os << " magent_code " << obj.magent_code ;
    //os << " funder_acct_id " << obj.funder_acct_id ;



    os << " " << obj.tx_id ;
    os << " " << obj.tx_type ;
    os << " " << obj.hypertag_id ;
    os << " " << obj.bank_code ;
    os << " " << obj.agent_code ;
    os << " " << obj.cif_id ;
    os << " " << obj.acc_id ;
    os << " " << (int)obj.acc_type ;
    os << " " << obj.net_operator ;
    os << " " << obj.phone ;
    os << " " << obj.home_currency ;
    os << " " << obj.home_country ;
    os << " " << obj.home_province ;
    os << " " << obj.home_region ;
    os << " " << obj.home_city ;
    os << " " << obj.home_township ;
    os << " " << obj.date_birth ;
    os << " " << (int)obj.id_type ;
    os << " " << obj.id_no ;
    os << " " << obj.gender ;
    os << " " << (int)obj.occupation ;
    os << " " << obj.home_branch ;
    os << " " << obj.service_plan ;
    os << " " << obj.signup_loc ;
    os << " " << obj.signup_date ;
    os << " " << obj.magent_code ;
    os << " " << obj.funder_acct_id ;
    return os;
}
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
    prm.max_que_size = 30000000;
    prm.pool_size = 20;
    prm.commit_count = 1000;
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
    reg_obj.id_type = std::rand() % 10;
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
    for(int i=0; i< 10000000; i++)
    {
        reg_obj.tx_id = reg_obj.tx_id++ ;
        worker.persist(reg_obj);
    }
    finished = true;
    th.join();
    worker.finalize();
    return 0;
}
