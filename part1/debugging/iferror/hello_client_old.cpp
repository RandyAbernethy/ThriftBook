#include "gen-cpp/HelloSvc.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <string>

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   
using boost::shared_ptr;
using boost::make_shared;

int main() {
    shared_ptr<TTransport> trans = make_shared<TSocket>("localhost", 9090);
    trans = make_shared<TBufferedTransport>(trans);
    auto proto = make_shared<TJSONProtocol>(trans);
    auto client = make_shared<HelloSvcClient>(proto);

    trans->open();
    int msg = client->hello_func("Zaphod", "Beeblebrox");
    std::cout << "[Client] received: " << msg << std::endl;
    trans->close();
}

