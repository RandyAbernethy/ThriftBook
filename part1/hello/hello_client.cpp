// Apache Thrift Hello World C++ Client

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/HelloSvc.h"

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   

int main() {
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 8585));
    socket->open();
    boost::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(socket));

    HelloSvcClient client(protocol);
    std::string msg;
    client.hello_func(msg);
    std::cout << "[Client] received: " << msg << std::endl;
}

