#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/helloSvc.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

int main() {
    boost::shared_ptr<TTransport> trans;
    trans = boost::make_shared<TSocket>("localhost", 8585);
    trans = boost::make_shared<TBufferedTransport>(trans);
    auto proto = boost::make_shared<TBinaryProtocol>(trans);
    helloSvcClient client(proto);

    try {
        trans->open();
        std::string msg;
        client.getMessage(msg, "world!");
        std::cout << msg << std::endl;
    } catch(...) {
        std::cout << "Client threw an exception" << std::endl;
    } 
    trans->close();
}
