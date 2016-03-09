#include "fxcm/HistoryBuilder.h"


int main(int argc, char* argv[]) {

  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  google::LogToStderr(); //info log

  return HistoryBuilder::execute();

}
