#include <iostream>					
#include <string>					
#include <boost/shared_ptr.hpp>			
#include <boost/make_shared.hpp>			
#include "../thrift/lib/cpp/src/thrift/transport/TServerSocket.h"
#include "../thrift/lib/cpp/src/thrift/protocol/TBinaryProtocol.h"
#include "../thrift/lib/cpp/src/thrift/server/TSimpleServer.h"
#include "../thrift/lib/cpp/src/thrift/TProcessor.h"
#include "gen-cpp/tree_types.h"			
#include "gen-cpp/simple.h"			

using namespace ::boost;
using namespace ::apache::thrift::transport;  	
using namespace ::apache::thrift::protocol;   	
using namespace ::apache::thrift::server;

int nc(const tree* pt) {
  return (nullptr == pt) ? 0 : (1+nc(pt->left)+nc(pt->right));
}

class simpleHandler : public simpleIf {
public:
  virtual void hello(const std::string& msg, const tree& t) override {
    std::cout << "hello msg: " << msg << ", tree nodes: " << nc(&t) << std::endl;
  }
};

int main(int argc, char **argv) {
  auto handler = make_shared<simpleHandler>();	
  auto proc = make_shared<simpleProcessor>(handler);
  auto svr_trans = make_shared<TServerSocket>(8585);
  auto trans_fac = make_shared<TTransportFactory>();
  auto proto_fac = make_shared<TBinaryProtocolFactory>();
  TSimpleServer server(proc, svr_trans, trans_fac, proto_fac);
  server.serve();
}

