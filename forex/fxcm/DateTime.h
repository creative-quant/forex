#ifndef _FXCM_DATETIME_
#define _FXCM_DATETIME_

#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;
using namespace boost::gregorian;

namespace fxcm {
  class DateTime {
  public:
    static ptime oleTimeToPtime ( const double &oleTime );
    static boost::posix_time::time_duration getEpochDuration ( const ptime &pTime );
    static double ptimeToOleTime( const ptime &pTime );
    static const ptime EPOCH;
    static const ptime OLE;
  };
}

#endif
