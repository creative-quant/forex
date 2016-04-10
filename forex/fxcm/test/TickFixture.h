#ifndef _FXCM_TEST_TICKFIXTURE_
#define _FXCM_TEST_TICKFIXTURE_

#include "ForexConnect.h"
#include <array>
#include <atomic>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include "gtest/gtest.h"

struct TickFixture : IO2GMarketDataSnapshotResponseReader {

  struct tick {

    DATE date;
    double bid;
    double ask;
    int vol;

    friend std::ostream& operator<<(std::ostream& os, const tick & t) {
      return os << std::setprecision( std::numeric_limits<long double>::digits10-3 ) << "tick { date: " << t.date <<
          " bid: " << t.bid << " ask: " << t.ask << "}\n";
    }

    friend bool operator==(const tick& t1, const tick& t2) {
      if( std::fabs(t1.date - t2.date) < 1.0/(24*60*60*1000) ) {
        testing::internal::Double t1d(t1.bid), t2d(t2.bid);
        if( t1d.AlmostEquals( t2d ) ) {
          t1d = testing::internal::Double(t1.ask);
          t2d = testing::internal::Double(t2.ask);
          if( t1d.AlmostEquals( t2d ) ) {
            return true;
          }
        }
      }
      return false;
    }
  };

  std::array<tick,8> mData = {{
                               { 42117.0000208912, 0.774620, 0.774650, 0 }
                               ,{ 42117.0000216319, 0.774602, 0.774611, 0 }
                               ,{ 42117.0000217319, 0.774601, 0.774699, 0 }
                               ,{ 42117.0000218319, 0.774619, 0.774669, 0 }
                               ,{ 42117.0000219319, 0.774620, 0.774670, 0 }
                               ,{ 42117.0000219329, 0.774620, 0.774660, 0 }
                               ,{ 42117.0000230208, 0.774630, 0.774660, 0 }
                               ,{ 42117.0000288194, 0.774640, 0.774660, 0 }

  }};

  public:
  std::atomic<long> mRefCount;

  TickFixture():mRefCount(1){}
//

  bool isBar() {
    return false;
  }

  int size() {
    return mData.size();
  }

  DATE getDate ( int index ) {
    return mData.at(index).date;
  }

  double getBid (int index) {
    return mData.at(index).bid;
  }

  double getAsk ( int index ) {
    return mData.at(index).ask;
  }

  long addRef() {
//    return 0;
    return ++mRefCount;
  }
  long release() {
//    return 0;
//    printf("TickFixture::release %ld\n", mRefCount - 1);
     if (--mRefCount == 0) {
       printf("!!!!!!!     0     !!!!!!!!!!!!\n");
       delete this;
       return 0;
     }
     if( mRefCount.load() == 1 ) {
       printf("!!!!!!!     1     !!!!!!!!!!!!\n");
     }
     return mRefCount;
  }
  double getBidOpen (int index) {
    throw "getBidOpen() - NOT IMPLEMENTED";
  }
  double getBidHigh(int index) {
    throw "getBidHigh() - NOT IMPLEMENTED";
  }
  double getBidLow(int index) {
    throw "getBidLow() - NOT IMPLEMENTED";
  }
  double getBidClose(int index) {
    throw "getBidClose() - NOT IMPLEMENTED";
  }
  double getAskOpen(int index) {
    throw "getAskOpen() - NOT IMPLEMENTED";
  }
  double getAskHigh(int index) {
   throw "getAskHigh() - NOT IMPLEMENTED";
  }
  double getAskLow(int index) {
    throw "getAskLow() - NOT IMPLEMENTED";
  }
  double getAskClose(int index) {
    throw "getAskClose() - NOT IMPLEMENTED";
  }
  int getVolume(int index) {
    return mData.at(index).vol;
  }
  int getLastBarVolume() {
    throw "getLastBarVolume() - NOT IMPLEMENTED";
  }
  DATE getLastBarTime() {
    throw "getLastBarTime() - NOT IMPLEMENTED";
  }

  protected:
  ~TickFixture(){}

};

#endif
