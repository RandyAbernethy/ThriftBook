// Apache Thrift Hello World C++ Client

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/HelloSvc.h"

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   
using boost::make_shared;

int main() {
    auto socket = make_shared<TSocket>("localhost", 9095);
    socket->open();
    auto protocol = make_shared<TBinaryProtocol>(socket);

    HelloSvcClient client(protocol);
    std::string msg;
    client.hello_func(msg);
    std::cout << "[Client] received: " << msg << std::endl;
}

