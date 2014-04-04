// Apache Thrift User Defined Exception Client in C++ 

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/TradeHistory.h"
#include "gen-cpp/excep_types.h"

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   

int main(int argv, char * argc[]) {
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 8585));
    socket->open();
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(socket));
    TradeHistoryClient client(protocol);
    try {
        double price = client.GetLastSale(argc[1]);
        std::cout << "[Client] received: " << price << std::endl;
    } catch (const BadFish & bf) {
        std::cout << "[Client] GetLastSale() call failed for fish: " << bf.fish << ", error: " << bf.error_code << std::endl;
    } catch (...) {								
        std::cout << "[Client] GetLastSale() call failed" << std::endl;
    }
}

