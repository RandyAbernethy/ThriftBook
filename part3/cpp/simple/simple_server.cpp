#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <thrift/server/TSimpleServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/TProcessor.h>
#include "gen-cpp/Message.h"

using namespace ::apache::thrift::server;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift;
using boost::shared_ptr;
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
    shared_ptr<MessageIf> handler = make_shared<MessageHandler>();
    shared_ptr<TProcessor> proc = make_shared<MessageProcessor>(handler);
    shared_ptr<TServerTransport> svr_trans = make_shared<TServerSocket>(8585);
    shared_ptr<TTransportFactory> trans_fac = make_shared<TBufferedTransportFactory>();
    shared_ptr<TProtocolFactory> proto_fac = make_shared<TBinaryProtocolFactory>();
    TSimpleServer server(proc, svr_trans, trans_fac, proto_fac);
    server.serve();
    return 0;
}
