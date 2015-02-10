// Apache Thrift Hello World C++ Client

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/HelloSvc.h"

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   
using boost::make_shared;

int main() {
    auto trans_ep = make_shared<TSocket>("localhost", 9095);
    auto trans_buf = make_shared<TBufferedTransport>(trans_ep);
    auto proto = make_shared<TBinaryProtocol>(trans_buf);
    HelloSvcClient client(proto);

    trans_ep->open();
    std::string msg;
    client.hello_func(msg);
    std::cout << "[Client] received: " << msg << std::endl;
}

