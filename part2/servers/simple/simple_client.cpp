#include "gen-cpp/Message.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using boost::make_shared;
using boost::shared_ptr;

int main() {
    shared_ptr<TTransport> trans;
    trans = make_shared<TSocket>("localhost", 9090);
    trans = make_shared<TBufferedTransport>(trans);
    auto proto = make_shared<TBinaryProtocol>(trans);
    MessageClient client(proto);

    trans->open();
    std::string msg;
    for (auto i = 0; i < 3; ++i) {
        client.motd(msg);
        std::cout << msg << std::endl;
    }
    trans->close();
}
