// Apache Thrift File Transport in C++

#include <thrift/transport/TSimpleFileTransport.h>
#include <iostream>
#include <cstring>

using namespace apache::thrift::transport;

struct Trade {
    char symbol[16];
    double price;
    int size;
};

int main() {
    TSimpleFileTransport trans_out("data", false, true);
    Trade trade{ "F", 13.10, 2500 };
    trans_out.write(reinterpret_cast<const uint8_t *>(&trade), sizeof(trade));
    trans_out.close();

    TSimpleFileTransport trans_in("data", true, false);	
    std::memset(&trade, 0, sizeof(trade));
    int bytes_read = trans_in.read(reinterpret_cast<uint8_t *>(&trade), sizeof(trade));

    std::cout << "Trade(" << bytes_read << "): " << trade.symbol 
              << " " << trade.size << " @ " << trade.price 
              << std::endl;
}

