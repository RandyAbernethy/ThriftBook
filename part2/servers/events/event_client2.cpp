#include "gen-cpp/Message.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <memory>
#include <iostream>
#include <string>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using std::shared_ptr;

class ThriftProxy {
public:
    ThriftProxy() :
        trans = make_shared<TSocket>("localhost", 9090),
        proto = make_shared<TCompactProtocol>(trans),
        client_(proto) 
    {
        trans->open();
    }
    
    ~ThriftProxy() 
    {
        trans->close();
    }
    
    static MessageClient & client() {
        static ThriftProxy proxy;
        return proxy.client_;
    }
    
private:
    shared_ptr<TTransport> trans;
    shared_ptr<TProtocol> proto;
    MessageClient client_;
};

int main(int argv, char * argc[]) {
    std::string msg;
    do {
        ThriftProxy::client().motd(msg);
        std::cout << msg << std::endl;
        std::cout << "Enter to call motd, 'q' to quit" << std::endl;
        std::getline(std::cin, msg);
    } while (0 != msg.compare("q"));
}
