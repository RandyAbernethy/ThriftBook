#include <iostream>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TJSONProtocol.h>
#include "gen-cpp/Message.h"					

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   

int main(int argv, char * argc[]) {
    boost::shared_ptr<TTransport> trans(new TSocket("localhost", 8585));
    trans.reset(new TFramedTransport(trans));
    trans->open();
    boost::shared_ptr<TProtocol> proto(new TJSONProtocol(trans));
    MessageClient client(proto);

    std::string msg;
    for (int i = 0; i < 3; ++i) {
        client.motd(msg);
        std::cout << msg << std::endl;
    }
    trans->close();
}

