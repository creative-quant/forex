#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DateTimeTest
#include <boost/test/unit_test.hpp>
#include <stdio.h>
#include "fxcm/dateTime.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

BOOST_AUTO_TEST_SUITE(DateTimeTest)

BOOST_AUTO_TEST_CASE( oleTimeToPtime ) {
  
  using namespace boost::gregorian;
  using namespace boost::posix_time;
  using namespace fxcm;

  // https://msdn.microsoft.com/en-us/library/38wh24td.aspx
  BOOST_CHECK_EQUAL( DateTime::oleTimeToPtime( -2.25 ), ptime(date(1899,12,28),hours(-6)) );
  BOOST_CHECK_EQUAL( DateTime::oleTimeToPtime( -1.0 ), ptime(date(1899,12,29)) );
  BOOST_CHECK_EQUAL( DateTime::oleTimeToPtime( -1.25 ), ptime(date(1899,12,29),hours(-6)) );
  BOOST_CHECK_EQUAL( DateTime::oleTimeToPtime( 0 ), ptime(date(1899,12,30)) );
  BOOST_CHECK_EQUAL( DateTime::oleTimeToPtime( 1.0 ), ptime(date(1899,12,31)) );
  BOOST_CHECK_EQUAL( DateTime::oleTimeToPtime( 2.25 ), ptime(date(1900,1,1),hours(6)) );
  
  ptime pt = DateTime::oleTimeToPtime( 42148.09037037 );
  time_duration td = DateTime::getEpochDuration( pt );
  BOOST_CHECK_EQUAL( pt, ptime(date(2015,5,24),hours(2)+minutes(10)+seconds(8) ) );
  BOOST_CHECK_EQUAL( td.total_seconds(), 1432433408 );
  BOOST_CHECK_EQUAL( td.total_milliseconds(), 1432433408000 );
}

BOOST_AUTO_TEST_CASE( ptimeToOleTime ) {

  using namespace boost::gregorian;
  using namespace boost::posix_time;
  using namespace fxcm;

  // https://msdn.microsoft.com/en-us/library/38wh24td.aspx
  BOOST_CHECK_EQUAL( DateTime::ptimeToOleTime( ptime(date(1899,12,28),hours(-6)) ), -2.25 );
  BOOST_CHECK_EQUAL( DateTime::ptimeToOleTime( ptime(date(1899,12,29)) ), -1.0 );
  BOOST_CHECK_EQUAL( DateTime::ptimeToOleTime( ptime(date(1899,12,29),hours(-6)) ), -1.25 );
  BOOST_CHECK_EQUAL( DateTime::ptimeToOleTime( ptime(date(1899,12,30)) ), 0 );
  BOOST_CHECK_EQUAL( DateTime::ptimeToOleTime( ptime(date(1899,12,31)) ), 1.0 );
  BOOST_CHECK_EQUAL( DateTime::ptimeToOleTime( ptime(date(1900,1,1),hours(6)) ), 2.25 );

  BOOST_REQUIRE_CLOSE( DateTime::ptimeToOleTime( ptime(date(2015,5,24),hours(2)+minutes(10)+seconds(8)+milliseconds(1) ) ), 42148.0903703816, 0.0000000001 );

}

BOOST_AUTO_TEST_SUITE_END()

