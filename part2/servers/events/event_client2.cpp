#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TCompactProtocol.h>
#include "gen-cpp/Message.h"                    

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   

class ThriftProxy {
public:
    ThriftProxy() :
        trans(new TSocket("localhost", 8585)),
        proto(new TCompactProtocol(trans)),
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
    boost::shared_ptr<TSocket> trans;
    boost::shared_ptr<TProtocol> proto;
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
