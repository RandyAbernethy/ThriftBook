// Apache Thrift Hello World C++ Client

#include "gen-cpp/HelloSvc.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
// Use boost for older versions of thrift
//#include <boost/make_shared.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   
// Use boost for older versions of thrift
//using boost::make_shared;
using std::make_shared;

int main() {
    auto trans_ep = make_shared<TSocket>("localhost", 9090);
    auto trans_buf = make_shared<TBufferedTransport>(trans_ep);
    auto proto = make_shared<TBinaryProtocol>(trans_buf);
    HelloSvcClient client(proto);

    trans_ep->open();
    std::string msg;
    client.hello_func(msg);
    std::cout << "[Client] received: " << msg << std::endl;
    trans_ep->close();
}

