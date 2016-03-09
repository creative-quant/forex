#include <ForexConnect.h>
#include <iostream>
#include <folly/futures/Future.h>
#include <stdexcept>
#include <glog/logging.h>
#include <iomanip>
#include "Client.h"
#include "Response.h"
#include <folly/Memory.h>

using namespace std;


namespace fxcm {

Client::Client ( IO2GSession *session, const std::string &symbol, const string &unit ) {
  mSymbol = symbol;

	mSession = session;
	session->addRef();

  mFactory = mSession->getRequestFactory();
  mFactory->addRef();

  mTimeframe = mFactory->getTimeFrameCollection()->get(unit.c_str());

  mTimeframe->addRef();
}

Client::~Client() {
  if( mSession != nullptr ) {
    mSession->release();
  }
  if( mFactory != nullptr ) {
    mFactory->release();
  }
  if( mTimeframe != nullptr ) {
    mTimeframe->release();
  }
}

Response::FutureDataSnapshot Client::request ( const DATE &from, const DATE &to ) {

  auto mRequest = mFactory->createMarketDataSnapshotRequestInstrument( mSymbol.c_str(), mTimeframe, mTimeframe->getQueryDepth());

  mFactory->fillMarketDataSnapshotRequestTime(mRequest, from, to, true);

  auto p = O2G2Ptr<Response>( new Response( mSession, mRequest->getRequestID() ) );

  mSession->sendRequest(mRequest);

  return p->getFuture();
}

}//fxcm






