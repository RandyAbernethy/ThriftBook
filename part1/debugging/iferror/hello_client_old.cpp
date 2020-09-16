#include "gen-cpp/HelloSvc.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <memory>
#include <iostream>
#include <string>

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   
using std::shared_ptr;
using std::make_shared;

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

