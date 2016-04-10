#include "fxcm/CSV.h"
#include "fxcm/DateTime.h"
#include "ForexConnect.h"
#include "TickFixture.h"
#include "fxcm/DataSnapshot.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CSVTest
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using namespace fxcm;

BOOST_AUTO_TEST_CASE( write_data_test ) {

  using boost::test_tools::output_test_stream;

  const std::string f = "/tmp/test_csv_tick_response.csv";

  auto dsrf = O2G2Ptr<TickFixture>( new TickFixture() );
  DataSnapshot r{ dsrf };

  CSV csv{ f };
  csv.onData( r );

  output_test_stream output( f, true );

  output << "datetime,bid,ask,volume" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:02.490000,0.77464,0.77466,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:01.989000,0.77463,0.77466,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:01.895000,0.77462,0.77466,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:01.895000,0.77462,0.77467,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:01.886000,0.774619,0.774669,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:01.878000,0.774601,0.774699,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:01.869000,0.774602,0.774611,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "2015-Apr-23 00:00:01.805000,0.77462,0.77465,0" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  std::remove(f.c_str());


}

