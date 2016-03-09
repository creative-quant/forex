#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "fxcm/test/TickFixture.h"
#include "fxcm/DataSnapshot.h"
#include <ForexConnect.h>

using namespace fxcm;

TEST( DataSnapshotTest, Test_copy_move ) {

  auto tf = O2G2Ptr<TickFixture>( new TickFixture() );

  //init !() destruct
  ASSERT_FALSE( !!DataSnapshot{} );
  ASSERT_TRUE( !!DataSnapshot{tf} );
  ASSERT_EQ( tf->mRefCount.load(), 1 );

  //copy
  auto ds = DataSnapshot{tf};
  auto tmp = DataSnapshot{ds};
  ASSERT_TRUE( !!tmp );
  ASSERT_EQ( tmp.data, tf );
  ASSERT_EQ( ds.data, tf );
  ASSERT_EQ( tf->mRefCount.load(), 3 );

  ds = tmp;
  ASSERT_TRUE( !!ds );
  ASSERT_EQ( tf->mRefCount.load(), 3 );

  //move
  auto ds2 = std::move( ds );
  ASSERT_EQ( ds.data, nullptr );
  ASSERT_TRUE( !!ds2 );
  ASSERT_FALSE( !!ds );
  ASSERT_EQ( tf->mRefCount.load(), 3 );

  ds = std::move(ds2);
  ASSERT_EQ( tf->mRefCount.load(), 3 );
  ASSERT_EQ( ds2.data, nullptr );
  ASSERT_TRUE( !!ds );
  ASSERT_FALSE( !!ds2 );

}


int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
