// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef REQ_AGENT_ODB_HPP
#define REQ_AGENT_ODB_HPP

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "req_agent.hpp"

#include <memory>
#include <cstddef>
#include <utility>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/no-id-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // ns2__reg_agent_obj
  //
  template <>
  struct class_traits< ::ns2__reg_agent_obj >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::ns2__reg_agent_obj >
  {
    public:
    typedef ::ns2__reg_agent_obj object_type;
    typedef ::ns2__reg_agent_obj* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef void id_type;

    static const bool auto_id = false;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_id_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_id_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };

  // ns2__reg_customer_obj
  //
  template <>
  struct class_traits< ::ns2__reg_customer_obj >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::ns2__reg_customer_obj >
  {
    public:
    typedef ::ns2__reg_customer_obj object_type;
    typedef ::ns2__reg_customer_obj* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef void id_type;

    static const bool auto_id = false;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_id_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_id_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/binding.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
  // ns2__reg_agent_obj
  //
  template <typename A>
  struct query_columns< ::ns2__reg_agent_obj, id_oracle, A >
  {
    // tx_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    tx_id_type_;

    static const tx_id_type_ tx_id;

    // tx_type
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint16_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    tx_type_type_;

    static const tx_type_type_ tx_type;

    // hypertag_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    hypertag_id_type_;

    static const hypertag_id_type_ hypertag_id;

    // bank_code
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint32_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    bank_code_type_;

    static const bank_code_type_ bank_code;

    // agent_code
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    agent_code_type_;

    static const agent_code_type_ agent_code;

    // cif_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    cif_id_type_;

    static const cif_id_type_ cif_id;

    // acc_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    acc_id_type_;

    static const acc_id_type_ acc_id;

    // acc_type
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint8_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    acc_type_type_;

    static const acc_type_type_ acc_type;

    // net_operator
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    net_operator_type_;

    static const net_operator_type_ net_operator;

    // phone
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    phone_type_;

    static const phone_type_ phone;

    // home_currency
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint16_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    home_currency_type_;

    static const home_currency_type_ home_currency;

    // home_country
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_country_type_;

    static const home_country_type_ home_country;

    // home_province
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_province_type_;

    static const home_province_type_ home_province;

    // home_region
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_region_type_;

    static const home_region_type_ home_region;

    // home_city
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_city_type_;

    static const home_city_type_ home_city;

    // home_township
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_township_type_;

    static const home_township_type_ home_township;

    // date_birth
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    date_birth_type_;

    static const date_birth_type_ date_birth;

    // id_type
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint8_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    id_type_type_;

    static const id_type_type_ id_type;

    // id_no
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    id_no_type_;

    static const id_no_type_ id_no;

    // gender
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    gender_type_;

    static const gender_type_ gender;

    // occupation
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint8_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    occupation_type_;

    static const occupation_type_ occupation;

    // home_branch
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_branch_type_;

    static const home_branch_type_ home_branch;

    // service_plan
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    service_plan_type_;

    static const service_plan_type_ service_plan;

    // signup_loc
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    signup_loc_type_;

    static const signup_loc_type_ signup_loc;

    // signup_date
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    signup_date_type_;

    static const signup_date_type_ signup_date;

    // magent_code
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    magent_code_type_;

    static const magent_code_type_ magent_code;

    // funder_acct_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    funder_acct_id_type_;

    static const funder_acct_id_type_ funder_acct_id;
  };

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::tx_id_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  tx_id (A::table_name, "\"tx_id\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::tx_type_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  tx_type (A::table_name, "\"tx_type\"", 0, 5);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::hypertag_id_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  hypertag_id (A::table_name, "\"hypertag_id\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::bank_code_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  bank_code (A::table_name, "\"bank_code\"", 0, 10);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::agent_code_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  agent_code (A::table_name, "\"agent_code\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::cif_id_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  cif_id (A::table_name, "\"cif_id\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::acc_id_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  acc_id (A::table_name, "\"acc_id\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::acc_type_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  acc_type (A::table_name, "\"acc_type\"", 0, 3);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::net_operator_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  net_operator (A::table_name, "\"net_operator\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::phone_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  phone (A::table_name, "\"phone\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::home_currency_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  home_currency (A::table_name, "\"home_currency\"", 0, 5);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::home_country_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  home_country (A::table_name, "\"home_country\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::home_province_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  home_province (A::table_name, "\"home_province\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::home_region_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  home_region (A::table_name, "\"home_region\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::home_city_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  home_city (A::table_name, "\"home_city\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::home_township_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  home_township (A::table_name, "\"home_township\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::date_birth_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  date_birth (A::table_name, "\"date_birth\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::id_type_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  id_type (A::table_name, "\"id_type\"", 0, 3);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::id_no_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  id_no (A::table_name, "\"id_no\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::gender_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  gender (A::table_name, "\"gender\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::occupation_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  occupation (A::table_name, "\"occupation\"", 0, 3);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::home_branch_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  home_branch (A::table_name, "\"home_branch\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::service_plan_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  service_plan (A::table_name, "\"service_plan\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::signup_loc_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  signup_loc (A::table_name, "\"signup_loc\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::signup_date_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  signup_date (A::table_name, "\"signup_date\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::magent_code_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  magent_code (A::table_name, "\"magent_code\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_agent_obj, id_oracle, A >::funder_acct_id_type_
  query_columns< ::ns2__reg_agent_obj, id_oracle, A >::
  funder_acct_id (A::table_name, "\"funder_acct_id\"", 0, 512);

  template <typename A>
  struct pointer_query_columns< ::ns2__reg_agent_obj, id_oracle, A >:
    query_columns< ::ns2__reg_agent_obj, id_oracle, A >
  {
  };

  template <>
  class access::object_traits_impl< ::ns2__reg_agent_obj, id_oracle >:
    public access::object_traits< ::ns2__reg_agent_obj >
  {
    public:
    static const std::size_t batch = 1UL;

    struct image_type
    {
      // tx_id
      //
      char tx_id_value[12];
      ub2 tx_id_size;
      sb2 tx_id_indicator;

      // tx_type
      //
      unsigned int tx_type_value;
      sb2 tx_type_indicator;

      // hypertag_id
      //
      char hypertag_id_value[12];
      ub2 hypertag_id_size;
      sb2 hypertag_id_indicator;

      // bank_code
      //
      unsigned int bank_code_value;
      sb2 bank_code_indicator;

      // agent_code
      //
      char agent_code_value[512];
      ub2 agent_code_size;
      sb2 agent_code_indicator;

      // cif_id
      //
      char cif_id_value[12];
      ub2 cif_id_size;
      sb2 cif_id_indicator;

      // acc_id
      //
      char acc_id_value[512];
      ub2 acc_id_size;
      sb2 acc_id_indicator;

      // acc_type
      //
      unsigned int acc_type_value;
      sb2 acc_type_indicator;

      // net_operator
      //
      char net_operator_value[512];
      ub2 net_operator_size;
      sb2 net_operator_indicator;

      // phone
      //
      char phone_value[12];
      ub2 phone_size;
      sb2 phone_indicator;

      // home_currency
      //
      unsigned int home_currency_value;
      sb2 home_currency_indicator;

      // home_country
      //
      char home_country_value[512];
      ub2 home_country_size;
      sb2 home_country_indicator;

      // home_province
      //
      char home_province_value[512];
      ub2 home_province_size;
      sb2 home_province_indicator;

      // home_region
      //
      char home_region_value[512];
      ub2 home_region_size;
      sb2 home_region_indicator;

      // home_city
      //
      char home_city_value[512];
      ub2 home_city_size;
      sb2 home_city_indicator;

      // home_township
      //
      char home_township_value[512];
      ub2 home_township_size;
      sb2 home_township_indicator;

      // date_birth
      //
      char date_birth_value[512];
      ub2 date_birth_size;
      sb2 date_birth_indicator;

      // id_type
      //
      unsigned int id_type_value;
      sb2 id_type_indicator;

      // id_no
      //
      char id_no_value[512];
      ub2 id_no_size;
      sb2 id_no_indicator;

      // gender
      //
      char gender_value[512];
      ub2 gender_size;
      sb2 gender_indicator;

      // occupation
      //
      unsigned int occupation_value;
      sb2 occupation_indicator;

      // home_branch
      //
      char home_branch_value[512];
      ub2 home_branch_size;
      sb2 home_branch_indicator;

      // service_plan
      //
      char service_plan_value[512];
      ub2 service_plan_size;
      sb2 service_plan_indicator;

      // signup_loc
      //
      char signup_loc_value[512];
      ub2 signup_loc_size;
      sb2 signup_loc_indicator;

      // signup_date
      //
      char signup_date_value[512];
      ub2 signup_date_size;
      sb2 signup_date_indicator;

      // magent_code
      //
      char magent_code_value[512];
      ub2 magent_code_size;
      sb2 magent_code_indicator;

      // funder_acct_id
      //
      char funder_acct_id_value[512];
      ub2 funder_acct_id_size;
      sb2 funder_acct_id_indicator;

      std::size_t version;

      oracle::change_callback change_callback_;

      oracle::change_callback*
      change_callback ()
      {
        return &change_callback_;
      }
    };

    using object_traits<object_type>::id;

    static void
    bind (oracle::bind*,
          image_type&,
          oracle::statement_kind);

    static void
    init (image_type&,
          const object_type&,
          oracle::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    typedef oracle::no_id_object_statements<object_type> statements_type;

    typedef oracle::query_base query_base_type;

    static const std::size_t column_count = 27UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
  };

  template <>
  class access::object_traits_impl< ::ns2__reg_agent_obj, id_common >:
    public access::object_traits_impl< ::ns2__reg_agent_obj, id_oracle >
  {
  };

  // ns2__reg_customer_obj
  //
  template <typename A>
  struct query_columns< ::ns2__reg_customer_obj, id_oracle, A >
  {
    // tx_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    tx_id_type_;

    static const tx_id_type_ tx_id;

    // tx_type
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint16_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    tx_type_type_;

    static const tx_type_type_ tx_type;

    // hypertag_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    hypertag_id_type_;

    static const hypertag_id_type_ hypertag_id;

    // bank_code
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint32_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    bank_code_type_;

    static const bank_code_type_ bank_code;

    // cif_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    cif_id_type_;

    static const cif_id_type_ cif_id;

    // acc_id
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    acc_id_type_;

    static const acc_id_type_ acc_id;

    // acc_type
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint8_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    acc_type_type_;

    static const acc_type_type_ acc_type;

    // net_operator
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    net_operator_type_;

    static const net_operator_type_ net_operator;

    // phone
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    phone_type_;

    static const phone_type_ phone;

    // home_currency
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint16_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    home_currency_type_;

    static const home_currency_type_ home_currency;

    // home_country
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_country_type_;

    static const home_country_type_ home_country;

    // home_province
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_province_type_;

    static const home_province_type_ home_province;

    // home_region
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_region_type_;

    static const home_region_type_ home_region;

    // home_city
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_city_type_;

    static const home_city_type_ home_city;

    // home_township
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_township_type_;

    static const home_township_type_ home_township;

    // date_birth
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    date_birth_type_;

    static const date_birth_type_ date_birth;

    // id_type
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint8_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    id_type_type_;

    static const id_type_type_ id_type;

    // id_no
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    id_no_type_;

    static const id_no_type_ id_no;

    // gender
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    gender_type_;

    static const gender_type_ gender;

    // occupation
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint8_t,
        oracle::id_int32 >::query_type,
      oracle::id_int32 >
    occupation_type_;

    static const occupation_type_ occupation;

    // home_branch
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_branch_type_;

    static const home_branch_type_ home_branch;

    // service_plan
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    service_plan_type_;

    static const service_plan_type_ service_plan;

    // signup_loc
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    signup_loc_type_;

    static const signup_loc_type_ signup_loc;

    // signup_date
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    signup_date_type_;

    static const signup_date_type_ signup_date;

    // agent_code
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    agent_code_type_;

    static const agent_code_type_ agent_code;

    // initial_deposit
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::uint64_t,
        oracle::id_big_int >::query_type,
      oracle::id_big_int >
    initial_deposit_type_;

    static const initial_deposit_type_ initial_deposit;
  };

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::tx_id_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  tx_id (A::table_name, "\"tx_id\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::tx_type_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  tx_type (A::table_name, "\"tx_type\"", 0, 5);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::hypertag_id_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  hypertag_id (A::table_name, "\"hypertag_id\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::bank_code_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  bank_code (A::table_name, "\"bank_code\"", 0, 10);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::cif_id_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  cif_id (A::table_name, "\"cif_id\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::acc_id_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  acc_id (A::table_name, "\"acc_id\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::acc_type_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  acc_type (A::table_name, "\"acc_type\"", 0, 3);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::net_operator_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  net_operator (A::table_name, "\"net_operator\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::phone_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  phone (A::table_name, "\"phone\"", 0, 20);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::home_currency_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  home_currency (A::table_name, "\"home_currency\"", 0, 5);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::home_country_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  home_country (A::table_name, "\"home_country\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::home_province_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  home_province (A::table_name, "\"home_province\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::home_region_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  home_region (A::table_name, "\"home_region\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::home_city_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  home_city (A::table_name, "\"home_city\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::home_township_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  home_township (A::table_name, "\"home_township\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::date_birth_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  date_birth (A::table_name, "\"date_birth\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::id_type_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  id_type (A::table_name, "\"id_type\"", 0, 3);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::id_no_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  id_no (A::table_name, "\"id_no\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::gender_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  gender (A::table_name, "\"gender\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::occupation_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  occupation (A::table_name, "\"occupation\"", 0, 3);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::home_branch_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  home_branch (A::table_name, "\"home_branch\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::service_plan_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  service_plan (A::table_name, "\"service_plan\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::signup_loc_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  signup_loc (A::table_name, "\"signup_loc\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::signup_date_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  signup_date (A::table_name, "\"signup_date\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::agent_code_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  agent_code (A::table_name, "\"agent_code\"", 0, 512);

  template <typename A>
  const typename query_columns< ::ns2__reg_customer_obj, id_oracle, A >::initial_deposit_type_
  query_columns< ::ns2__reg_customer_obj, id_oracle, A >::
  initial_deposit (A::table_name, "\"initial_deposit\"", 0, 20);

  template <typename A>
  struct pointer_query_columns< ::ns2__reg_customer_obj, id_oracle, A >:
    query_columns< ::ns2__reg_customer_obj, id_oracle, A >
  {
  };

  template <>
  class access::object_traits_impl< ::ns2__reg_customer_obj, id_oracle >:
    public access::object_traits< ::ns2__reg_customer_obj >
  {
    public:
    static const std::size_t batch = 1UL;

    struct image_type
    {
      // tx_id
      //
      char tx_id_value[12];
      ub2 tx_id_size;
      sb2 tx_id_indicator;

      // tx_type
      //
      unsigned int tx_type_value;
      sb2 tx_type_indicator;

      // hypertag_id
      //
      char hypertag_id_value[12];
      ub2 hypertag_id_size;
      sb2 hypertag_id_indicator;

      // bank_code
      //
      unsigned int bank_code_value;
      sb2 bank_code_indicator;

      // cif_id
      //
      char cif_id_value[12];
      ub2 cif_id_size;
      sb2 cif_id_indicator;

      // acc_id
      //
      char acc_id_value[512];
      ub2 acc_id_size;
      sb2 acc_id_indicator;

      // acc_type
      //
      unsigned int acc_type_value;
      sb2 acc_type_indicator;

      // net_operator
      //
      char net_operator_value[512];
      ub2 net_operator_size;
      sb2 net_operator_indicator;

      // phone
      //
      char phone_value[12];
      ub2 phone_size;
      sb2 phone_indicator;

      // home_currency
      //
      unsigned int home_currency_value;
      sb2 home_currency_indicator;

      // home_country
      //
      char home_country_value[512];
      ub2 home_country_size;
      sb2 home_country_indicator;

      // home_province
      //
      char home_province_value[512];
      ub2 home_province_size;
      sb2 home_province_indicator;

      // home_region
      //
      char home_region_value[512];
      ub2 home_region_size;
      sb2 home_region_indicator;

      // home_city
      //
      char home_city_value[512];
      ub2 home_city_size;
      sb2 home_city_indicator;

      // home_township
      //
      char home_township_value[512];
      ub2 home_township_size;
      sb2 home_township_indicator;

      // date_birth
      //
      char date_birth_value[512];
      ub2 date_birth_size;
      sb2 date_birth_indicator;

      // id_type
      //
      unsigned int id_type_value;
      sb2 id_type_indicator;

      // id_no
      //
      char id_no_value[512];
      ub2 id_no_size;
      sb2 id_no_indicator;

      // gender
      //
      char gender_value[512];
      ub2 gender_size;
      sb2 gender_indicator;

      // occupation
      //
      unsigned int occupation_value;
      sb2 occupation_indicator;

      // home_branch
      //
      char home_branch_value[512];
      ub2 home_branch_size;
      sb2 home_branch_indicator;

      // service_plan
      //
      char service_plan_value[512];
      ub2 service_plan_size;
      sb2 service_plan_indicator;

      // signup_loc
      //
      char signup_loc_value[512];
      ub2 signup_loc_size;
      sb2 signup_loc_indicator;

      // signup_date
      //
      char signup_date_value[512];
      ub2 signup_date_size;
      sb2 signup_date_indicator;

      // agent_code
      //
      char agent_code_value[512];
      ub2 agent_code_size;
      sb2 agent_code_indicator;

      // initial_deposit
      //
      char initial_deposit_value[12];
      ub2 initial_deposit_size;
      sb2 initial_deposit_indicator;

      std::size_t version;

      oracle::change_callback change_callback_;

      oracle::change_callback*
      change_callback ()
      {
        return &change_callback_;
      }
    };

    using object_traits<object_type>::id;

    static void
    bind (oracle::bind*,
          image_type&,
          oracle::statement_kind);

    static void
    init (image_type&,
          const object_type&,
          oracle::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    typedef oracle::no_id_object_statements<object_type> statements_type;

    typedef oracle::query_base query_base_type;

    static const std::size_t column_count = 26UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
  };

  template <>
  class access::object_traits_impl< ::ns2__reg_customer_obj, id_common >:
    public access::object_traits_impl< ::ns2__reg_customer_obj, id_oracle >
  {
  };

  // ns2__reg_agent_obj
  //
  // ns2__reg_customer_obj
  //
}

#include "req_agent_odb_inline.hpp"

#include <odb/post.hxx>

#endif // REQ_AGENT_ODB_HPP
