#include "gen-cpp/Message.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/TProcessor.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift;
using boost::make_shared;

const char * msgs[] = {"Apache Thrift!!",
                       "Childhood is a short season",
                       "'Twas brillig"};

class MessageHandler : public MessageIf {
public:
    MessageHandler() : msg_index(0) {;}
    virtual void motd(std::string& _return) override {
        std::cout << "Call count: " << ++msg_index << std::endl;
        _return = msgs[msg_index%3];
    }
private:
    unsigned int msg_index;
};

int main() {
    MessageProcessor proc(make_shared<MessageHandler>());
    TServerSocket trans_svr(9090);
    trans_svr.listen();
    while (true) {
        auto trans = make_shared<TBufferedTransport>(trans_svr.accept());
        auto proto = make_shared<TBinaryProtocol>(trans);
  	try{
	    while(proc.process(proto, proto, nullptr)) {;}
        } catch (const TTransportException& ex) {
            std::cout << ex.what() << ", waiting for next client" << std::endl;
        }
    }
}
