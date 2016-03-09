#ifndef _FXCM_TEST_MOCKIO2GSESSION_
#define _FXCM_TEST_MOCKIO2GSESSION_

class MockIO2GSession : public IO2GSession {
 public:
  MOCK_METHOD0(addRef,
        long());
    MOCK_METHOD0(release,
        long());
  MOCK_METHOD0(getLoginRules,
      IO2GLoginRules*());
  MOCK_METHOD4(login,
      void(const char *user, const char *pwd, const char *url, const char *connection));
  MOCK_METHOD0(logout,
      void());
  MOCK_METHOD1(subscribeSessionStatus,
      void(IO2GSessionStatus *listener));
  MOCK_METHOD1(unsubscribeSessionStatus,
      void(IO2GSessionStatus *listener));
  MOCK_METHOD0(getTradingSessionDescriptors,
      IO2GSessionDescriptorCollection*());
  MOCK_METHOD2(setTradingSession,
      void(const char *sessionId, const char *pin));
  MOCK_METHOD1(subscribeResponse,
      void(IO2GResponseListener *listener));
  MOCK_METHOD1(unsubscribeResponse,
      void(IO2GResponseListener *listener));
  MOCK_METHOD0(getRequestFactory,
      IO2GRequestFactory*());
  MOCK_METHOD0(getResponseReaderFactory,
      IO2GResponseReaderFactory*());
  MOCK_METHOD1(sendRequest,
      void(IO2GRequest *request));
  MOCK_METHOD0(getTimeConverter,
      IO2GTimeConverter*());
  MOCK_METHOD1(setPriceUpdateMode,
      void(O2GPriceUpdateMode mode));
  MOCK_METHOD0(getPriceUpdateMode,
      O2GPriceUpdateMode());
  MOCK_METHOD0(getServerTime,
      DATE());
  MOCK_METHOD9(getReportURL,
      int(char* urlBuffer, int bufferSize, IO2GAccountRow* account, DATE dateFrom, DATE dateTo, const char* format, const char* reportType, const char* langID, long ansiCP));
  MOCK_METHOD0(getTableManager,
      IO2GTableManager*());
  MOCK_METHOD1(getTableManagerByAccount,
      IO2GTableManager*(const char *accountID));
  MOCK_METHOD2(useTableManager,
      void(O2GTableManagerMode mode, IO2GTableManagerListener *tablesListener));
  MOCK_METHOD0(getSessionStatus,
      IO2GSessionStatus::O2GSessionStatus());
};



#endif
