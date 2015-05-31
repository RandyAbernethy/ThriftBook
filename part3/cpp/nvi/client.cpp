#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/NVITest.h"
#include "gen-cpp/nvi_types.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

int main() {
    boost::shared_ptr<TTransport> trans;
    trans = boost::make_shared<TSocket>("localhost", 8585);
    trans = boost::make_shared<TBufferedTransport>(trans);
    auto proto = boost::make_shared<TBinaryProtocol>(trans);
    NVITestClient client(proto);

    trans->open();
    Trade trade;
    trade.symbol = "F";
    trade.price = 13.10;
    trade.size = 2500;
    for (auto i = 0; i < 1000000; ++i) {
        client.report_trade(trade);
    }
    trans->close();
}
