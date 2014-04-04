// Apache Thrift User Defined Exception Server in C++

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "gen-cpp/TradeHistory.h"
#include "gen-cpp/excep_types.h"

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

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
  shared_ptr<TradeHistoryHandler> handler(new TradeHistoryHandler());
  shared_ptr<TProcessor> processor(new TradeHistoryProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(
                                       new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(
                                       new TBinaryProtocolFactory());
  TSimpleServer server(processor, serverTransport, 
                       transportFactory, protocolFactory);
  server.serve();
  return 0;
}

