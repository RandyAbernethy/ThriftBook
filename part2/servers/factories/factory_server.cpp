#include "gen-cpp/Message.h"
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransport.h>
#include <thrift/TProcessor.h>
#include <memory>
#include <iostream>
#include <string>

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift;
using std::make_shared;
using std::shared_ptr;

const char * msgs[] = {"Apache Thrift!!",
                       "Childhood is a short season",
                       "'Twas brillig"};

class MessageHandler : public MessageIf {
public:
    MessageHandler(int conn_no) : 
        msg_index(0), connection_no(conn_no) {;}
    virtual void motd(std::string& _return) override {
        std::cout << "[" << connection_no << "] Call count: "
                  << ++msg_index << std::endl;
        _return = msgs[msg_index%3];
    }
private:
    unsigned int msg_index;
    unsigned int connection_no;
};


class MessageHandlerFactory : public MessageIfFactory {
public:
    MessageHandlerFactory() : connection_no(0) {;}
    virtual MessageIf* getHandler(const TConnectionInfo& connInfo) {
        return new MessageHandler(++connection_no);
    };
    virtual void releaseHandler(MessageIf* handler) {
        delete handler;
    };
private:
    unsigned int connection_no;
};


int main(int argc, char **argv) {
    auto handler_fac = make_shared<MessageHandlerFactory>();
    auto proc_fac = make_shared<MessageProcessorFactory>(handler_fac);

    auto trans_svr = make_shared<TServerSocket>(9090);
    auto trans_fac = make_shared<TFramedTransportFactory>();
    auto proto_fac = make_shared<TJSONProtocolFactory>();

    TThreadedServer server(proc_fac, trans_svr, trans_fac, proto_fac);
    server.serve();
}

