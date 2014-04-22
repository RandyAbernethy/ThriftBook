#include <iostream>					
#include <string>					
#include <boost/shared_ptr.hpp>			
#include <boost/make_shared.hpp>			
#include "../thrift/lib/cpp/src/thrift/transport/TSocket.h"
#include "../thrift/lib/cpp/src/thrift/protocol/TBinaryProtocol.h"
#include "gen-cpp/tree_types.h"			
#include "gen-cpp/simple.h"			

using namespace boost;
using namespace apache::thrift::transport;  	
using namespace apache::thrift::protocol;   	

int main() {						
    auto socket = make_shared<TSocket>("localhost", 8585);
    auto protocol = make_shared<TBinaryProtocol>(socket);
    simpleClient client { protocol };
    socket->open();

    tree root;
    root.left = new tree();
    root.right = new tree();
    client.hello("Hi", root);
}

