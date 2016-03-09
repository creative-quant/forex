#include <ForexConnect.h>
#include <folly/futures/Promise.h>
#include "Client.h"
#include "Response.h"
#include "DataSnapshot.h"

using namespace std;
using namespace folly;

namespace fxcm {

Response::Response(IO2GSession *session, const std::string &requestID ) {
  mRefCount = 1;
  mRequestID = requestID;
  mSession = session;
  mSession->addRef();
  mSession->subscribeResponse(this);
}

Response::~Response () {
  if( mSession != nullptr ) {
    if( !mPromise.isFulfilled() ) {
      mSession->unsubscribeResponse(this);
    }
    mSession->release();
  }
  mSession = nullptr;
}

void Response::onRequestCompleted(const char *requestId, IO2GResponse *response ) {
  if (response != nullptr && mRequestID == requestId) {
    if( response->getType() == MarketDataSnapshot ) {
      auto factory = mSession->getResponseReaderFactory();
      if( factory != nullptr && factory != NULL ) {
        mPromise.setValue( DataSnapshot{ factory->createMarketDataSnapshotReader(response) } );
      }
      else {
        LOG(ERROR) << "IO2GResponseReaderFactory is a nullptr";
        mPromise.setException(make_exception_wrapper<runtime_error>( "IO2GResponseReaderFactory is a nullptr" ) );
      }
      mSession->unsubscribeResponse(this);
    }
  }
}

void Response::onRequestFailed(const char *requestId , const char *error) {
  if (mRequestID == requestId) {
    LOG(ERROR) << error;
    mPromise.setException(make_exception_wrapper<runtime_error>( error ) );
    mSession->unsubscribeResponse(this);
  }
}

}

