#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/Message.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

int main() {
    boost::shared_ptr<TTransport> trans;
    trans = boost::make_shared<TSocket>("localhost", 8585);
    trans = boost::make_shared<TBufferedTransport>(trans);
    auto proto = boost::make_shared<TBinaryProtocol>(trans);
    MessageClient client(proto);

    trans->open();
    std::string msg;
    for (auto i = 0; i < 3; ++i) {
        client.motd(msg);
        std::cout << msg << std::endl;
    }
    trans->close();
}
