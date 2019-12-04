#ifndef REQ_AGENT_HPP
#define REQ_AGENT_HPP
#include<string>
#include<ostream>
#include<odb/core.hxx>



struct ns2__reg_agent_obj
{
    uint64_t tx_id ;//
    uint16_t tx_type;//
    uint64_t hypertag_id;//
    uint32_t bank_code;//
    std::string agent_code;//
    uint64_t cif_id;
    std::string acc_id;
    uint8_t acc_type;
    std::string net_operator;
};
#pragma db object(ns2__reg_agent_obj) no_id




struct ns2__reg_customer_obj
{
    uint64_t tx_id ;//
    uint16_t tx_type;//
    uint64_t hypertag_id;//
    std::string signup_date;
    std::string agent_code;
    uint64_t initial_deposit;
};
#pragma db object(ns2__reg_customer_obj) no_id


#pragma db view table("ns2__reg_agent_obj")
struct count_reg_agent
{
      #pragma db column("count(*)") type("NUMBER")
      int cnt;
};



#endif
