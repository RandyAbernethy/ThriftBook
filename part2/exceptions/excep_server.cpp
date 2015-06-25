// Apache Thrift User Defined Exception Server in C++

#include "gen-cpp/TradeHistory.h"
#include "gen-cpp/excep_types.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using boost::shared_ptr;
using boost::make_shared;

class TradeHistoryHandler : virtual public TradeHistoryIf {
public:
    double GetLastSale(const std::string& fish) override {
        if (0 != fish.compare("Halibut")) {
            BadFish bf;
            bf.fish = fish;
            bf.error_code = 94;
            throw bf;
        }
        return 10.0;
    }
};

int main(int argc, char **argv) {
  int port = 9090;

  auto handler = make_shared<TradeHistoryHandler>();
  auto proc = make_shared<TradeHistoryProcessor>(handler);
  auto trans_svr = make_shared<TServerSocket>(port);
  auto trans_fac = make_shared<TBufferedTransportFactory>();
  auto proto_fac = make_shared<TBinaryProtocolFactory>();

  TSimpleServer server(proc, trans_svr, trans_fac, proto_fac);
  server.serve();
  return 0;
}
