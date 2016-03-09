#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <ForexConnect.h>
#include "fxcm/Client.h"
#include "MockIO2GSession.h"
#include "fxcm/test/TickFixture.h"
#include "MockIO2GResponseReaderFactory.h"
#include "MockIO2GResponse.h"
#include <folly/Memory.h>

using namespace std;
using namespace testing;
using namespace fxcm;


class MockIO2GTimeframeCollection : public IO2GTimeframeCollection {
 public:
  MOCK_METHOD0(addRef,
        long());
    MOCK_METHOD0(release,
        long());
  MOCK_METHOD0(size,
      int());
  MOCK_METHOD1(get,
      IO2GTimeframe*(int index));
  MOCK_METHOD1(get,
      IO2GTimeframe*(const char *id));
};

class MockIO2GTimeframe : public IO2GTimeframe {
 public:
  MOCK_METHOD0(addRef,
        long());
    MOCK_METHOD0(release,
        long());
  MOCK_METHOD0(getID,
      const char*());
  MOCK_METHOD0(getUnit,
      O2GTimeframeUnit());
  MOCK_METHOD0(getQueryDepth,
      int());
  MOCK_METHOD0(getSize,
      int());
};

class MockIO2GRequest : public IO2GRequest {
 public:
  MOCK_METHOD0(addRef,
            long());
        MOCK_METHOD0(release,
            long());
  const char *getRequestID() {
    return "FOO";
  }
  MOCK_METHOD0(getChildrenCount,
      int());
  MOCK_METHOD1(getChildRequest,
      IO2GRequest*(int index));
};

class MockIO2GRequestFactory : public IO2GRequestFactory {
 public:
  MOCK_METHOD0(addRef,
          long());
      MOCK_METHOD0(release,
          long());
  MOCK_METHOD0(getTimeFrameCollection,
      IO2GTimeframeCollection*());
  IO2GRequest* createMarketDataSnapshotRequestInstrument (const char *instrument,
      IO2GTimeframe *timeframe,
      int maxBars = 300) {
    return getMockIO2GRequest();
  }
  void fillMarketDataSnapshotRequestTime (IO2GRequest *request, DATE timeFrom = 0, DATE timeTo = 0, bool isIncludeWeekends = false) {}
  MOCK_METHOD1(createRefreshTableRequest,
      IO2GRequest*(O2GTable table));
  MOCK_METHOD2(createRefreshTableRequestByAccount,
      IO2GRequest*(O2GTable table, const char* account));
  MOCK_METHOD1(createOrderRequest,
      IO2GRequest*(IO2GValueMap *valueMap));
  MOCK_METHOD0(createValueMap,
      IO2GValueMap*());
  MOCK_METHOD0(getLastError,
      const char*());

  MockIO2GRequest* getMockIO2GRequest() {
    return mMockIO2GRequest.get();
  }

 private:
 std::shared_ptr<MockIO2GRequest> mMockIO2GRequest = std::make_shared<MockIO2GRequest>();
};


TEST( ClientTest, request ) {

  auto s = make_unique<MockIO2GSession>();
  auto rf = make_unique<MockIO2GRequestFactory>();
  auto tc = make_unique<MockIO2GTimeframeCollection>();
  auto tf = make_unique<MockIO2GTimeframe>();
  auto mr = make_unique<MockIO2GResponse>();
  auto rrf = make_unique<MockIO2GResponseReaderFactory>();
  auto dsrf = O2G2Ptr<TickFixture>( new TickFixture() );

  //client constructor overrides
  ON_CALL( *s, getRequestFactory() )
     .WillByDefault( Return( rf.get() ) );

  ON_CALL( *rf, getTimeFrameCollection() )
      .WillByDefault( Return( tc.get() ) );

  ON_CALL( *tc, get(O2GTimeframeUnit::Tick) )
    .WillByDefault( Return( tf.get() ) );

  // request overrides
  // overridden in mock obj
  // mFactory->createMarketDataSnapshotRequestInstrument
  // mFactory->fillMarketDataSnapshotRequestTime
  // mRequest->getRequestID()

  // response overrides
  ON_CALL( *mr, getType() ).WillByDefault(Return(MarketDataSnapshot));

  ON_CALL( *s, getResponseReaderFactory())
    .WillByDefault(Return( rrf.get()) );

  ON_CALL( *rrf, createMarketDataSnapshotReader( mr.get() ) )
    .WillByDefault( Return(dsrf) );

  //create hook to call onRequestCompleted
  IO2GResponseListener * myListener = nullptr;
  //mimic subscriptions calls
  ON_CALL( *s, subscribeResponse(_) )
  .WillByDefault(Invoke(
      [&myListener](IO2GResponseListener *listener){
        myListener = listener;
        listener->addRef();
      }
  ));

  ON_CALL( *s, unsubscribeResponse(_) )
    .WillByDefault(Invoke(
        [&myListener](IO2GResponseListener *listener){
          listener->release();
        }
    ));

  auto c = make_unique<Client>( s.get(), "FOO", O2GTimeframeUnit::Tick );
  auto f = c->request( DATE{}, DATE{} );
  myListener->onRequestCompleted( "FOO", mr.get() );

  ASSERT_TRUE( !!f.value() );
  ASSERT_EQ( f.value().data, dsrf );
}


int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
