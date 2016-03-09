#ifndef _FXCM_CLIENT_
#define _FXCM_CLIENT_

#include <stdio.h>
#include <ForexConnect.h>
#include <atomic>
#include <boost/signals2/signal.hpp>
#include <boost/thread.hpp>
#include <folly/futures/Promise.h>
#include <folly/futures/Future.h>
#include <vector>
#include <folly/futures/InlineExecutor.h>
#include "fxcm/Response.h"

namespace fxcm {

class Client
{
  public:
	Client( IO2GSession *session, const std::string &symbol, const string &unit );
	Response::FutureDataSnapshot request (const DATE &from, const DATE &to );
	~Client();

  private:
	IO2GSession *mSession = nullptr;
  IO2GRequestFactory *mFactory = nullptr;
  IO2GTimeframe *mTimeframe = nullptr;
  std::string mSymbol;

};

}
#endif
