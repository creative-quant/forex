#include "fxcm/CSV.h"
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

  output << "datetime,bid,ask" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000288194,0.77464,0.77466" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000230208,0.77463,0.77466" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000219329,0.77462,0.77466" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000219319,0.77462,0.77467" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000218319,0.774619,0.774669" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000217319,0.774601,0.774699" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000216319,0.774602,0.774611" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  output << "42117.0000208912,0.77462,0.77465" << std::endl;
  BOOST_CHECK( output.match_pattern() );

  dsrf->release();

  std::remove(f.c_str());


}

