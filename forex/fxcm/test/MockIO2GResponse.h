#ifndef _FXCM_TEST_MOCKIO2GRESPONSE_
#define _FXCM_TEST_MOCKIO2GRESPONSE_

#include "gmock/gmock.h"
#include <ForexConnect.h>

class MockIO2GResponse : public IO2GResponse {
 public:
  MOCK_METHOD0(addRef,
        long());
    MOCK_METHOD0(release,
        long());
  MOCK_METHOD0(getType,
      O2GResponseType());
  MOCK_METHOD0(getRequestID,
      const char*());
};

#endif
