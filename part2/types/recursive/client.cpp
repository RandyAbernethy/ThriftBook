#include "gen-cpp/tree_types.h"
#include "gen-cpp/simple.h"
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <boost/make_shared.hpp>
#include <iostream>
#include <string>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using boost::make_shared;

int main() {
    auto trans = make_shared<TSocket>("localhost", 9090);
    auto proto = make_shared<TBinaryProtocol>(trans);
    simpleClient client(proto);

    tree root;
    root.left = make_shared<tree>();
    root.right = make_shared<tree>();

    trans->open();
    client.hello("Hi", root);
    trans->close();
}

