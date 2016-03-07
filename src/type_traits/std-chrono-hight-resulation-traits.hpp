// file      : odb/boost/date-time/oracle/posix-time-traits.hxx
// copyright : Copyright (c) 2009-2015 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_BOOST_DATE_TIME_ORACLE_POSIX_TIME_TRAITS_HXX
#define ODB_BOOST_DATE_TIME_ORACLE_POSIX_TIME_TRAITS_HXX

#include <odb/pre.hxx>

#include <odb/core.hxx>

#include <odb/oracle/traits.hxx>
#include <odb/oracle/oracle-fwd.hxx>   // ub1, sb2, ub4
#include <odb/oracle/oracle-types.hxx> // odb::oracle::{datetime interval_ds}
#include <odb/oracle/details/date.hxx>

#include <chrono>
#include <ctime>
#include <time.h>
	

namespace odb
{
  namespace oracle
  {
    template <>
    struct default_value_traits< std::chrono::high_resolution_clock::time_point, id_timestamp>
    {
      typedef std::chrono::high_resolution_clock::time_point ptime;

  //    typedef ::boost::gregorian::date date;

      typedef ptime value_type;
      typedef ptime query_type;
      typedef datetime image_type;

      static void
      set_value (ptime& v, const datetime& i, bool is_null)
      {
        if (is_null)
        {
            v = std::chrono::system_clock::from_time_t(0);
        }
        else
        {
          sb2 y;
          ub1 m, d, h, minute, s;
          ub4 ns;
          std::tm tmtime ;

          i.get (y, m, d, h, minute, s, ns);

          unsigned long long fract_s (ns);
          
          tmtime.tm_sec = s ;
          tmtime.tm_min = minute ;
          tmtime.tm_hour = h ;
          tmtime.tm_mday = d ;
          tmtime.tm_mon = m - 1 ;
          tmtime.tm_year = y - 1900;
          std::time_t timet = timegm(&tmtime);
          v = std::chrono::system_clock::from_time_t(timet);
          v +=  std::chrono::microseconds((fract_s/1000));
        }
      }

      static void
      set_image (datetime& i, bool& is_null, const ptime& v)
      {
          is_null = false;
          std::tm tmtime ;
          time_t ttime =  std::chrono::system_clock::to_time_t(v);			
          gmtime_r(&ttime,&tmtime);

          std::chrono::nanoseconds nanosec= std::chrono::duration_cast<std::chrono::nanoseconds> (v.time_since_epoch() % std::chrono::seconds(1) );
          unsigned long long ns = nanosec.count();
          i.set (static_cast<sb2> (tmtime.tm_year + 1900),
                 static_cast<ub1> (tmtime.tm_mon + 1),
                 static_cast<ub1> (tmtime.tm_mday),
                 static_cast<ub1> (tmtime.tm_hour),
                 static_cast<ub1> (tmtime.tm_min),
                 static_cast<ub1> (tmtime.tm_sec),
                 static_cast<ub4> (ns));
      }
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_BOOST_DATE_TIME_ORACLE_POSIX_TIME_TRAITS_HXX
