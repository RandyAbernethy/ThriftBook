#include "gen-cpp/helloSvc.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <future>
#include <chrono>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using boost::shared_ptr;
using boost::make_shared;

int main() {
    shared_ptr<TTransport> trans;
    trans = make_shared<TSocket>("localhost", 9090);
    trans = make_shared<TBufferedTransport>(trans);
    auto proto = make_shared<TBinaryProtocol>(trans);
    helloSvcClient client(proto);

    try {
        trans->open();
        
        auto fut = std::async(std::launch::async, [&client]{
            std::string out; 
            client.getMessage(out, "world!"); 
            return out;
        });

        std::cout << "Client async call to getMessage() in progress" << std::endl;
        if (fut.wait_for(std::chrono::milliseconds(500)) == std::future_status::ready) {
            std::cout << fut.get() << std::endl;
        } else {
            throw "async call timed out";
        }
    } catch(...) {
        std::cout << "Client caught an exception" << std::endl;
    } 
    trans->close();
}
