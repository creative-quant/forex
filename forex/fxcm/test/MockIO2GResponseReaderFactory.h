#ifndef _FXCM_TEST_MOCKIO2GRESPONSEREADERFACTORY_
#define _FXCM_TEST_MOCKIO2GRESPONSEREADERFACTORY_

#include <ForexConnect.h>
#include "gmock/gmock.h"

class MockIO2GResponseReaderFactory : public IO2GResponseReaderFactory {
 public:
  MOCK_METHOD0(addRef,
          long());
      MOCK_METHOD0(release,
          long());
  MOCK_METHOD1(createTablesUpdatesReader,
      IO2GTablesUpdatesReader*(IO2GResponse *response));
  MOCK_METHOD1(createMarketDataSnapshotReader,
      IO2GMarketDataSnapshotResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createMarketDataReader,
      IO2GMarketDataResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createOffersTableReader,
      IO2GOffersTableResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createAccountsTableReader,
      IO2GAccountsTableResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createOrdersTableReader,
      IO2GOrdersTableResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createTradesTableReader,
      IO2GTradesTableResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createClosedTradesTableReader,
      IO2GClosedTradesTableResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createMessagesTableReader,
      IO2GMessagesTableResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createOrderResponseReader,
      IO2GOrderResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createLastOrderUpdateResponseReader,
      IO2GLastOrderUpdateResponseReader*(IO2GResponse *response));
  MOCK_METHOD1(createSystemPropertiesReader,
      IO2GSystemPropertiesReader*(IO2GResponse *response));
  MOCK_METHOD1(processMarginRequirementsResponse,
      bool(IO2GResponse *response));
};



#endif
