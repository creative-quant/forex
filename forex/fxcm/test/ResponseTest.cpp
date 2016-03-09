#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <ForexConnect.h>
#include "fxcm/Response.h"
#include "fxcm/test/TickFixture.h"
#include "MockIO2GSession.h"
#include "MockIO2GResponseReaderFactory.h"
#include "MockIO2GResponse.h"
#include <folly/Memory.h>

using namespace std;
using namespace testing;
using namespace fxcm;
using namespace folly;


TEST( ResponseTest, onRequestCompleted ) {

  auto s = make_unique<MockIO2GSession>();
  auto rrf = make_unique<MockIO2GResponseReaderFactory>();
  auto tf = O2G2Ptr<IO2GMarketDataSnapshotResponseReader>( new TickFixture() );
  auto r = make_unique<MockIO2GResponse>();

  ON_CALL( *rrf, createMarketDataSnapshotReader(_) )
  .WillByDefault( Return( tf ) );

  ON_CALL( *s, getResponseReaderFactory())
  .WillByDefault(Return( rrf.get() ));

  ON_CALL( *r, getType() ).WillByDefault(Return(MarketDataSnapshot));

  auto res = O2G2Ptr<Response>(new Response( s.get(), "FOO"));
  auto fut = res->getFuture();
  res->onRequestCompleted( "FOO", r.get() );

  fut.wait();//sim block

  //future value
  ASSERT_FALSE( fut.hasException() );
  ASSERT_TRUE( fut.hasValue() );
  ASSERT_TRUE( !!fut.value() );
  ASSERT_EQ( fut.value().data, tf );

  //add release
  ASSERT_EQ( res->addRef(), 2 );
  ASSERT_EQ( res->release(), 1 );

}

TEST( ResponseTest, onRequestCompletedWithException ) {

  auto s = make_unique<MockIO2GSession>();
  auto r = make_unique<MockIO2GResponse>();

  ON_CALL( *r, getType() ).WillByDefault(Return(MarketDataSnapshot));

  auto res = O2G2Ptr<Response>(new Response(s.get(), "FOO"));
  auto fut = res->getFuture();
  res->onRequestCompleted( "FOO", r.get() );

  ASSERT_TRUE( fut.hasException() );
}

TEST( ResponseTest, onRequestFailed ) {

  auto ms = make_unique<MockIO2GSession>();

  auto r = O2G2Ptr<Response>(new Response(ms.get(), "FOO"));
  auto f = r->getFuture();
  r->onRequestFailed( "FOO", "testing fault" );

  ASSERT_TRUE( f.hasException() );

}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
