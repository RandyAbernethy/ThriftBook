#include "gen-cpp/helloSvc.h"
#include <thrift/transport/THttpClient.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <memory>
#include <iostream>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using std::make_shared;

int main() {
    auto trans = make_shared<THttpClient>("localhost", 9090, "/");
    auto proto = make_shared<TBinaryProtocol>(trans);
    helloSvcClient client(proto);

    try {
        trans->open();
        std::string msg;
        client.getMessage(msg, "world!");
        std::cout << msg << std::endl;
    } catch(...) {
        std::cout << "Client caught an exception" << std::endl;
    } 
    trans->close();
}
