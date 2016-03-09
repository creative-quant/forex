#ifndef _FXCM_SESSION_
#define _FXCM_SESSION_

#include <stdio.h>
#include <ForexConnect.h>
#include <atomic>
#include <folly/futures/Future.h>

using namespace std;

namespace fxcm {

class Session : public IO2GSessionStatus {

  IO2GSession *mSession;
  std::atomic<long> mRefCount;
  folly::Promise<bool> mPromise;

  ~Session();

public:

  Session( IO2GSession * session );

  /** Increase reference counter. */
  virtual long addRef();

  /** Decrease reference counter. */
  virtual long release();

  /** Callback called when login has been failed. */
  virtual void onLoginFailed(const char *error);

  /** Callback called when session status has been changed. */
  virtual void onSessionStatusChanged(IO2GSessionStatus::O2GSessionStatus status);

  folly::Future<bool> login(const string &user, const string &pwd, const string &url, const string &connection);

  void logout ();
};
}

#endif


