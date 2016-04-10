#ifndef _FXCM_CSV_
#define _FXCM_CSV_

#include <iostream>
#include <string>
#include <folly/File.h>
#include <folly/FileUtil.h>
#include "fxcm/DataSnapshot.h"
#include "ForexConnect.h"
#include "fxcm/DateTime.h"

using namespace std;
using namespace folly;

namespace fxcm {
class CSV {

  File mFile;

  public:
  CSV( const string &fileName ) : mFile{ fileName, O_WRONLY | O_CREAT  } {
    auto header = string{"datetime,bid,ask,volume\n"};
    writeFull( mFile.fd(), header.c_str(), header.size() );
  }

  CSV(const CSV&) = delete; //no copy
  CSV& operator = (const CSV&) = delete;
  CSV(CSV&&) = delete;//no move
  CSV& operator = (CSV&&) = delete;

  DataSnapshot onData(DataSnapshot r) {
    if( r ) {
      auto ss = std::stringstream{};
      ss.precision(std::numeric_limits<long double>::digits10-3);
      auto data = r.data;
      auto i =  data->size();
      while( (i--) > 0 ) {
        ss << to_simple_string( DateTime::oleTimeToPtime( data->getDate(i) ) )
            << "," << data->getBid(i) << "," << data->getAsk(i) << "," << data->getVolume(i) << "\n";
      }
      auto s = ss.tellp();
      ss.seekg(ios_base::beg);
      writeFull( mFile.fd(), ss.str().c_str(), s );
    }
    return r;
  }
};
}

#endif
