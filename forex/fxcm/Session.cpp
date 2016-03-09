#include "Session.h"

#include <folly/futures/Future.h>
#include <ForexConnect.h>
#include <glog/logging.h>
#include <stdexcept>

using namespace std;
using namespace folly;

namespace fxcm {

Session::Session( IO2GSession * session ) {
  mSession = session;
  mSession->addRef();
  mSession->subscribeSessionStatus(this);
  mRefCount = 1;
}

Session::~Session() {
  mSession->unsubscribeSessionStatus(this);
  mSession->release();
}

long Session::addRef() {
  return ++mRefCount;
}

long Session::release() {
  if (--mRefCount == 0) {
    delete this;
    return 0;
  }
  return mRefCount;
}

Future<bool> Session::login(const string &user,
                            const string &pwd,
                            const string &url,
                            const string &connection ) {

  mSession->login( user.c_str(), pwd.c_str(), url.c_str(), connection.c_str() );
  return mPromise.getFuture();
}

void Session::onLoginFailed(const char *error) {
  LOG(ERROR) << error;
  mPromise.setException(folly::make_exception_wrapper<std::runtime_error>("Login Failed"));
}

void Session::onSessionStatusChanged(IO2GSessionStatus::O2GSessionStatus status) {
  switch (status) {
    case IO2GSessionStatus::Disconnected:
      LOG(INFO) << "status::disconnected";
      if(!mPromise.isFulfilled()) {
        mPromise.setValue(false);
      }
      break;
    case IO2GSessionStatus::Connecting:
      LOG(INFO) << "status::connecting";
      break;
    case IO2GSessionStatus::TradingSessionRequested:
      LOG(INFO) << "status::trading session requested";
      break;
    case IO2GSessionStatus::Connected:
      LOG(INFO) << "status::connected";
      mPromise.setValue(true);
      break;
    case IO2GSessionStatus::Reconnecting:
      LOG(INFO) << "status::reconnecting";
      break;
    case IO2GSessionStatus::Disconnecting:
      LOG(INFO) << "status::disconnecting";
      break;
    case IO2GSessionStatus::SessionLost:
      LOG(INFO) << "status::session lost";
      break;
    case IO2GSessionStatus::PriceSessionReconnecting:
      LOG(INFO) << "status::price session reconnecting";
      break;
    case IO2GSessionStatus::ConnectedWithNeedToChangePassword:
      LOG(WARNING) << "status::connected with need to change password";
      break;
    default:
    LOG(ERROR) << "";
    }
}

void Session::logout () {
  if( mSession ) {
    mSession->logout();
  }
}

}
