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
    double GetLastSale(const std::string& fish) {
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
  int port = 8585;

  auto handler = make_shared<TradeHistoryHandler>();
  shared_ptr<TProcessor> proc =
    make_shared<TradeHistoryProcessor>(handler);
  shared_ptr<TServerTransport> svr_trans =
    make_shared<TServerSocket>(port);
  shared_ptr<TTransportFactory> trans_fac =
    make_shared<TBufferedTransportFactory>();
  shared_ptr<TProtocolFactory> proto_fac =
    make_shared<TBinaryProtocolFactory>();

  TSimpleServer server(proc, svr_trans, trans_fac, proto_fac);
  server.serve();
  return 0;
}
