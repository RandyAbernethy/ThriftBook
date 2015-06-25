// Apache Thrift User Defined Exception Client in C++

#include "gen-cpp/TradeHistory.h"
#include "gen-cpp/excep_types.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using boost::shared_ptr;
using boost::make_shared;

int main(int argv, char * argc[]) {
    shared_ptr<TTransport> trans;
    trans = make_shared<TSocket>("localhost", 9090);
    trans = make_shared<TBufferedTransport>(trans);
    auto proto = make_shared<TBinaryProtocol>(trans);
    TradeHistoryClient client(proto);

    try {
        trans->open();
        auto price = client.GetLastSale(argc[1]);
        std::cout << "[Client] received: " << price << std::endl;
    } catch (const BadFish & bf) {
        std::cout << "[Client] GetLastSale() call failed for fish: "
                  << bf.fish << ", error: " << bf.error_code << std::endl;
    } catch (...) {
        std::cout << "[Client] GetLastSale() call failed" << std::endl;
    }
    trans->close();
}
