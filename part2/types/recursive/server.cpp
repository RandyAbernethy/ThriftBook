#include "gen-cpp/tree_types.h"
#include "gen-cpp/simple.h"
#include <thrift/transport/TServerSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/TProcessor.h>
#include <memory>
#include <iostream>
#include <string>

using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::server;
using std::make_shared;

int node_count(const tree * t) {
  return (!t) ? 0 : (1 +
                    node_count(t->left.get()) +
                    node_count(t->right.get()));
}

class simpleHandler : public simpleIf {
public:
  virtual void hello(const std::string& msg, const tree& t) override {
    std::cout << "hello msg: " << msg
              << ", tree nodes: " << node_count(&t) << std::endl;
  }
};

int main(int argc, char **argv) {
  auto handler = make_shared<simpleHandler>();
  auto proc = make_shared<simpleProcessor>(handler);
  auto trans_svr = make_shared<TServerSocket>(9090);
  auto trans_fac = make_shared<TTransportFactory>();
  auto proto_fac = make_shared<TBinaryProtocolFactory>();
  TSimpleServer server(proc, trans_svr, trans_fac, proto_fac);
  server.serve();
}
