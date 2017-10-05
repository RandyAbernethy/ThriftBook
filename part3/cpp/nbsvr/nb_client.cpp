#include "gen-cpp/trade_report_types.h"
#include "gen-cpp/TradeHistory.h"
#include <thrift/Thrift.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <memory>
#include <iostream>
#include <string>


using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace TradeReporting;
using std::shared_ptr;
using std::make_shared;

int main() {
    auto trans_ep = make_shared<TSocket>("localhost", 9090);
    auto trans = make_shared<TFramedTransport>(trans_ep);
    auto proto = make_shared<TCompactProtocolT<TFramedTransport>>(trans);
    TradeHistoryClient client(proto);

    try {
        trans->open();
        std::string input;
        std::string symbol("APPL");
        TradeReport trade;
        do {
            client.get_last_sale(trade, symbol);
            std::cout << std::boolalpha 
                      << "[Client] trade(" << symbol << "): " 
                      << trade.seq_num << ">  " 
                      << trade.symbol << " " 
                      << trade.size  << " @ " 
                      << trade.price <<  std::endl;
            std::cout << "enter 'q' to quit, anything else to GetLastSale" << std::endl;
            std::getline(std::cin, input);
        } while (input[0] != 'q');
    } catch(const TTransportException& te) {
        std::cout << "Client caught a TTransportException: " << te.what() << std::endl;
    } catch(const TException& e) {
        std::cout << "Client caught a TException: " << e.what() << std::endl;
    } catch(...) {
        std::cout << "Client caught an exception" << std::endl;
    } 
    trans->close();
}
