#include "gen-cpp/helloSvc.h"
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace ::apache::thrift::server;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using boost::shared_ptr;
using boost::make_shared;

class helloSvcHandler : public helloSvcIf {
public:
    virtual void getMessage(std::string& _return, const std::string& name) override {
        std::cout << "Server received: " << name << ", from client" << std::endl;
        _return = "Hello " + name;
    }
};

int main() {
    auto handler = make_shared<helloSvcHandler>();
    auto proc = make_shared<helloSvcProcessor>(handler);
    auto trans_svr = make_shared<TServerSocket>(9090);
    auto trans_fac = make_shared<TBufferedTransportFactory>();
    auto proto_fac = make_shared<TBinaryProtocolFactory>();
    TSimpleServer server(proc, trans_svr, trans_fac, proto_fac);
    server.serve();
    return 0;
}
