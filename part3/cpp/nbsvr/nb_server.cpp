#include "gen-cpp/trade_report_types.h"
#include "gen-cpp/TradeHistory.h"
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/TProcessor.h>
#include <thrift/server/TNonblockingServer.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <functional>
#include <atomic>

using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift;
using namespace TradeReporting;
using boost::shared_ptr;
using boost::make_shared;

class TradeHistoryHandler : virtual public TradeHistoryIf {
public: 
    TradeHistoryHandler(const TConnectionInfo & ci, int con_count) : con_id(con_count), call_count(0) {
        TSocket * pSoc = dynamic_cast<TSocket *>(ci.transport.get());
        std::string soc_info;
        if (nullptr != pSoc) {
            soc_info = pSoc->getSocketInfo();
        }
        std::cout << "[Server] ConCreate:" <<  std::this_thread::get_id() 
                  << ':' << con_id << ':' << call_count 
                  << " (" << soc_info << ')' << std::endl;
    }
    virtual ~TradeHistoryHandler() {
        std::cout << "[Server] ConDelete:" <<  std::this_thread::get_id() 
                  << ':' << con_id << ':' << call_count << std::endl;
    }
    void GetLastSale(TradeReport& trade, const std::string& symbol) override {
        trade.seq_num = (con_id * 10000) + (++call_count);
        trade.symbol = symbol;
        if (0 == symbol.compare("APPL")) {
            trade.price = 127.61;
            trade.size = 500;
        } else if (0 == symbol.compare("MSFT")) {
            trade.price = 46.23;
            trade.size = 400;
        } else {
            trade.price = 0.0;
            trade.size = 0;
        }
        std::cout << "[Server] GetLastSale(" <<  std::this_thread::get_id() 
                  << ':' << con_id << ':' << call_count << ") returning: " 
                  << trade.seq_num << "> "
                  << trade.symbol << " - " << trade.size << " @ " 
                  << trade.price << std::endl;
    }
private: 
    const int con_id;
    int call_count;
};

class TradeHistoryIfInstanceFactory : virtual public TradeHistoryIfFactory {
public:
    TradeHistoryIfInstanceFactory() : con_count(0) {;}
    virtual TradeHistoryIf* getHandler(const TConnectionInfo & ci) { 
 		return new TradeHistoryHandler(ci, ++con_count); 
 	}
    virtual void releaseHandler(TradeHistoryIf * handler) { delete handler; }
private: 
    int con_count;
};


int main() {
    auto port = 9090;
    auto hw_threads = std::thread::hardware_concurrency();

    auto handler_fac = make_shared<TradeHistoryIfInstanceFactory>();
    auto proc_fac = make_shared<TradeHistoryProcessorFactory>(handler_fac);
    auto proto_fac = make_shared<TCompactProtocolFactoryT<TFramedTransport>>();
 
    TNonblockingServer server(proc_fac, proto_fac, port);
    server.setNumIOThreads(1 + hw_threads);
    std::thread server_thread(std::bind(&TNonblockingServer::serve, &server));

    std::string str;
    do {
        std::cout << "[Server:" << hw_threads << ':' << port << "] Enter 'q' to quit" << std::endl;
        std::getline(std::cin, str);
    } while (str[0] != 'q');

    server.stop();
    std::cout   << "waiting for server to exit..." << std::endl;
    server_thread.join();
    std::cout << "service complete, exiting." << std::endl;

    return 0;
}
