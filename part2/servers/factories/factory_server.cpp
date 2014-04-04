#include <string>
#include <boost/shared_ptr.hpp>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransport.h>
#include <thrift/TProcessor.h>
#include "gen-cpp/Message.h"

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift;
using boost::shared_ptr;

const char * msgs[] = {"Apache Thrift!!",
                       "Childhood is a short season",
                       "'Twas brillig"};
class MessageHandler : public MessageIf {
public:
    MessageHandler(int conn_no) : 
        msg_index(0), connection_no(conn_no) {;}
    virtual void motd(std::string& _return) override {
        std::cout << "[" << connection_no << "] Call count: " << ++msg_index << std::endl;
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
    shared_ptr<MessageIfFactory> handler_fac(new MessageHandlerFactory());
    shared_ptr<TProcessorFactory> proc_fac(new MessageProcessorFactory(handler_fac));

    shared_ptr<TServerTransport>  svr_trans(new TServerSocket(8585));
    shared_ptr<TTransportFactory> trans_fac(new TFramedTransportFactory());
    shared_ptr<TProtocolFactory>  proto_fac(new TJSONProtocolFactory());

    TThreadedServer server(proc_fac, svr_trans, trans_fac, proto_fac);
    server.serve();
}

