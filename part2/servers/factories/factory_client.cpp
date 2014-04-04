#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TJSONProtocol.h>
#include "gen-cpp/Message.h"                    

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   

int main(int argv, char * argc[]) {
    boost::shared_ptr<TTransport> trans(new TSocket("localhost", 8585));
    trans.reset(new TFramedTransport(trans));
    boost::shared_ptr<TProtocol> proto(new TJSONProtocol(trans));
    MessageClient client(proto);
    trans->open();

    std::string msg;
    do {
        client.motd(msg);
        std::cout << msg << std::endl;
        std::cout << "Enter to call motd, 'q' to quit" << std::endl;
        std::getline(std::cin, msg);
    } while (0 != msg.compare("q"));
    trans->close();
}

