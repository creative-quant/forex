#ifndef _FXCM_DATASNAPSHOT_
#define _FXCM_DATASNAPSHOT_

#include "ForexConnect.h"

namespace fxcm {

struct DataSnapshot {

  IO2GMarketDataSnapshotResponseReader * data = nullptr;

  DataSnapshot ( IO2GMarketDataSnapshotResponseReader * _data = nullptr ) : data(_data) {
    if( data != nullptr ) {
      data->addRef();
    }
  }

  ~DataSnapshot() {
    if( data != nullptr ) {
      data->release();
    }
    data = nullptr;
  }

  //copy
  DataSnapshot(const DataSnapshot& other) : data{ other.data } {
    if( data != nullptr ) {
      data->addRef();
    }
  }

  DataSnapshot& operator=(const DataSnapshot& other) {
    if( data != nullptr ) {
      data->release();
    }
    data = other.data;
    if( data != nullptr ) {
      data->addRef();
    }
    return *this;
  }

  //move
  DataSnapshot(DataSnapshot&& other) : data{ other.data } {
    if(data != nullptr) {
      data->addRef();
      other.~DataSnapshot();
    }
  }

  DataSnapshot& operator=(DataSnapshot&& other) {
    if( data != nullptr ) {
      data->release();
    }
    data = other.data;
    if(data != nullptr){
      data->addRef();
      other.~DataSnapshot();
    }
    return *this;
  }

  bool operator!() const { return data == nullptr; }
  operator bool() const { return data != nullptr; }
};

}

#endif /* FOREX_FXCM_DATASNAPSHOT_H_ */
