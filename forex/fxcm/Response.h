#ifndef _FXCM_RESPONSE_
#define _FXCM_RESPONSE_

#include <ForexConnect.h>
#include <folly/futures/Promise.h>
#include "DataSnapshot.h"

using namespace std;
using namespace folly;


namespace fxcm {

class Response : IO2GResponseListener {

  public:

  typedef Future<DataSnapshot> FutureDataSnapshot;

  Response ( IO2GSession *session, const std::string &requestID );

  Response(const Response&) = delete; //no copy
  Response& operator = (const Response&) = delete;
  Response(Response&&) = delete;//no move
  Response& operator = (Response&&) = delete;

  /** Increase reference counter. */
  virtual long addRef() {
    return ++mRefCount;
  }

  /** Decrease reference counter. */
  virtual long release() {
      if (--mRefCount == 0) {
        delete this;
        return 0;
      }
      return mRefCount;
  }

  /** Request execution completed data handler. */
  virtual void onRequestCompleted(const char *requestId, IO2GResponse *response = 0);

  /** Request execution failed data handler. */
  virtual void onRequestFailed(const char *requestId , const char *error);

  /** Request update data received data handler. */
  virtual void onTablesUpdates(IO2GResponse *data) {};

  FutureDataSnapshot getFuture () {
    return mPromise.getFuture();
  }

  protected:
  ~Response();

  private:
  Promise<DataSnapshot> mPromise;
  std::atomic<long> mRefCount;
  IO2GSession *mSession = nullptr;
  std::string mRequestID;

};
}

#endif
