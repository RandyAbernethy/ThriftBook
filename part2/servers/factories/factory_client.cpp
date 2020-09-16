#include "gen-cpp/Message.h"
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <memory>
#include <iostream>
#include <string>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using std::make_shared;
using std::shared_ptr;

int main(int argv, char * argc[]) {
    shared_ptr<TTransport> trans;
    trans = make_shared<TSocket>("localhost", 9090);
    trans = make_shared<TFramedTransport>(trans);
    auto proto = make_shared<TJSONProtocol>(trans);
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

