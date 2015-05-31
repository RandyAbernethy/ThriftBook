#include <boost/make_shared.hpp>
#include <thrift/server/TSimpleServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "gen-cpp/nvi_types.h"
#include "gen-cpp/NVITest.h"

using namespace ::apache::thrift::server;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using boost::make_shared;

class NVITestHandler : public NVITestIf {
public:
    NVITestHandler() : trade_count(0) { ; }
    int32_t report_trade(const Trade& trade) override {
        return ++trade_count;
    }
private:
    int32_t trade_count;
};

int main() {
    auto handler = make_shared<NVITestHandler>();
    auto proc = make_shared<NVITestProcessor>(handler);
    auto svr_trans = make_shared<TServerSocket>(8585);
    auto trans_fac = make_shared<TBufferedTransportFactory>();
    auto proto_fac = make_shared<TBinaryProtocolFactoryT<TBufferedTransport>>();
    TSimpleServer server(proc, svr_trans, trans_fac, proto_fac);
    server.serve();
    return 0;
}
