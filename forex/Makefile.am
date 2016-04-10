ACLOCAL_AMFLAGS = -I m4

TESTS = datetime_test \
  csv_test \
  #voltdb_test \
  response_test \
  data_snapshot_test \
  client_test

datetime_test_SOURCES = fxcm/DateTime.h \
  fxcm/DateTime.cpp \
  fxcm/test/DateTimeTest.cpp
  
datetime_test_LDADD = -lboost_unit_test_framework


csv_test_SOURCES = fxcm/test/CSVTest.cpp \
  fxcm/CSV.h \
  fxcm/test/TickFixture.h \
  fxcm/DateTime.h \
  fxcm/DateTime.cpp \
  fxcm/DataSnapshot.h

csv_test_LDADD = -lboost_unit_test_framework

#voltdb_test_SOURCES = fxcm/test/VoltDBTest.cpp \
#  fxcm/DateTime.h \
#  fxcm/DateTime.cpp \
#  fxcm/VoltDB.h \
#  fxcm/test/TickFixture.h

#voltdb_test_LDADD = -lgtest -lpthread -lgmock -lgmock_main

data_snapshot_test_SOURCES = fxcm/test/DataSnapshotTest.cpp \
  fxcm/test/TickFixture.h \
  fxcm/DataSnapshot.h

data_snapshot_test_LDADD = -lgtest -lpthread -lgmock -lgmock_main

response_test_SOURCES = fxcm/test/ResponseTest.cpp \
  fxcm/test/TickFixture.h \
  fxcm/test/MockIO2GSession.h \
  fxcm/DataSnapshot.h \
  fxcm/Response.h \
  fxcm/Response.cpp

response_test_LDADD = -lgtest -lpthread -lgmock -lgmock_main

client_test_SOURCES = fxcm/test/ClientTest.cpp \
  fxcm/Response.h \
  fxcm/Response.cpp \
  fxcm/test/MockIO2GSession.h \
  fxcm/Client.h \
  fxcm/Client.cpp

client_test_LDADD = -lgtest -lpthread -lgmock -lgmock_main


check_PROGRAMS = $(TESTS)

bin_PROGRAMS = forex

forex_includedir = ./
forex_include_HEADERS = fxcm/Session.h \
	fxcm/CSV.h \
	fxcm/DataSnapshot.h \
  fxcm/Response.h \
  fxcm/Client.h \
  fxcm/DateTime.h \
  fxcm/HistoryBuilder.h

forex_SOURCES = forex.cpp \
  fxcm/Session.cpp \
  fxcm/Response.cpp \
  fxcm/Client.cpp \
  fxcm/DateTime.cpp


