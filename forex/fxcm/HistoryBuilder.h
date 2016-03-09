#ifndef _FXCM_HISTORY_BUILDER_
#define _FXCM_HISTORY_BUILDER_

#include <iostream>
#include "ForexConnect.h"
#include <folly/futures/Future.h>
#include "glog/logging.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "fxcm/Session.h"
#include "fxcm/Client.h"
#include "fxcm/DataSnapshot.h"
#include "fxcm/DateTime.h"
#include "fxcm/CSV.h"
#include <wangle/concurrent/IOThreadPoolExecutor.h>
#include <folly/Memory.h>
#include <gflags/gflags.h>
#include <array>
#include <algorithm>

using namespace std;
using namespace fxcm;
using namespace folly;
using namespace boost::gregorian;
using namespace boost::posix_time;

DEFINE_string(user, "", "fxcm user name" );
DEFINE_string(password, "", "fxcm password" );
DEFINE_string(url, "http://www.fxcorporate.com/Hosts.jsp", "fxcm host url" );
DEFINE_string(account, "DEMO", "fxcm account type e.g. DEMO or REAL" );
DEFINE_string(symbol, "", "ticker symbol e.g. AUD/USD" );
DEFINE_string(timeframe, "day", "t1|m1|m5|m15|m30|H1|H2|H3|H4|H6|H8|D1|W1|M1" );
DEFINE_string(from, "", "year/month/date" );
DEFINE_string(to, "", "year/month/date" );
DEFINE_string(csv, "", "filename for csv output" );
DEFINE_int32(threads, 0, "Number of threads. Numbers <= 0"
             " will use the number of cores on this machine.");


namespace fxcm {

class HistoryBuilder {

  static string getUnit () {
    for( auto n: { "t1","m1","m5","m15","m30","H1","H2","H3","H4","H6","H8","D1","W1","M1" } ) {
      if( n == FLAGS_timeframe ) {
        return n;
      }
    }
    return "D1";
  }

  static DATE getDate ( const string& data ) {
    return DateTime::ptimeToOleTime(ptime(from_simple_string(data)));
  }

  public:

  static int execute() {

    if (FLAGS_threads <= 0) {
      FLAGS_threads = sysconf(_SC_NPROCESSORS_ONLN);
      CHECK(FLAGS_threads > 0);
    }

    auto from = getDate( FLAGS_from );
    auto to = getDate( FLAGS_to );

    auto TIMEOUT = Duration(10000);

    auto o2gsession = CO2GTransport::createSession();

    auto session = O2G2Ptr<Session>( new Session {o2gsession} );

    auto login = session->login( FLAGS_user, FLAGS_password, FLAGS_url, FLAGS_account )
    .onError( [](const exception& e) {
      return false;
    });

    if( login.get(TIMEOUT) ) {

      auto client = make_unique<Client>( o2gsession, FLAGS_symbol, getUnit() );

      auto io = make_unique<wangle::IOThreadPoolExecutor>( FLAGS_threads );
      auto csv = make_unique<CSV>( FLAGS_csv );

      auto current = to;

      while( from < current ) {
        auto ds = client->request( from, current )
            .onTimeout(TIMEOUT, []() {
              LOG(ERROR) << "fxcm request timed out";
              return DataSnapshot();
            })
            .onError( [](const exception& e) {
                return DataSnapshot();
            })
            .get();
        if( ds ) {
          current = ds.data->getDate( 0 );
          folly::via( io.get(), bind( &fxcm::CSV::onData, csv.get(), move(ds) ) );

        } else {
          break;
        }
      }

      io->join();

      session->logout();

      return 0;
    }
    return 1;
  }

};

}


#endif
