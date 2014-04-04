#include <iostream>
#include <boost/shared_ptr.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/TProcessor.h>
#include "gen-cpp/Message.h"					

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift;
using boost::shared_ptr;

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

int main(int argc, char **argv) {
    MessageProcessor proc(shared_ptr<MessageIf>(new MessageHandler()));
    TServerSocket svr_trans(8585);
    svr_trans.listen();
    while (true) {
  		shared_ptr<TProtocol> proto(new TBinaryProtocol(svr_trans.accept()));
  		try{
	  		while(proc.process(proto, proto, nullptr)) {;}
	  	} catch (TTransportException ex) {
	  		std::cout << ex.what() << ", waiting for next client" << std::endl;
	  	}
    }
}

