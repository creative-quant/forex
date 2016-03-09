#include "datetime.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include <math.h>

using namespace boost::posix_time;
using namespace boost::gregorian;

const ptime fxcm::DateTime::EPOCH( date(1970,1,1) );
const ptime fxcm::DateTime::OLE( date(1899,12,30 ));

ptime fxcm::DateTime::oleTimeToPtime ( const double &oleTime ) {
  days d(oleTime);
  long long msecs = llround((oleTime - d.days()) * 24 * 60 * 60 * 1000);
  return OLE + days(d) + milliseconds( msecs );
}

double fxcm::DateTime::ptimeToOleTime ( const boost::posix_time::ptime &pTime ) {
  time_duration diff = pTime - OLE;
  return (diff.total_milliseconds() / 24.0 / 60.0 / 60.0 / 1000.0);
}

time_duration fxcm::DateTime::getEpochDuration ( const ptime &pTime ) {
  return time_duration(pTime - EPOCH);
}

