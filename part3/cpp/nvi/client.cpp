#include "gen-cpp/NVITest.h"
#include "gen-cpp/nvi_types.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <memory>
#include <iostream>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace apache::thrift::protocol;
using std::shared_ptr;
using std::make_shared;

int main() {
    shared_ptr<TTransport> trans;
    trans = make_shared<TSocket>("localhost", 8585);
    trans = make_shared<TBufferedTransport>(trans);
    auto proto = make_shared<TBinaryProtocol>(trans);
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
