// Apache Thrift Memory Transport in C++ 

#include <iostream>
#include <thrift/transport/TBufferTransports.h>

struct Trade {
   char symbol[16];
   double price;
   int size;
};

int main() {
    apache::thrift::transport::TMemoryBuffer transport(4096);

    Trade trade;
    trade.symbol[0] = 'F'; trade.symbol[1] = '\0';
    trade.price = 13.10;
    trade.size = 2500;
    transport.write((const uint8_t *)&trade, sizeof(trade));

    Trade trade_read;
    int bytes_read = transport.read((uint8_t *)&trade_read, sizeof(trade_read));

    std::cout << "Trade(" << bytes_read << "): " << trade_read.symbol << " " 
 			  << trade_read.size << " @ " << trade_read.price << std::endl;
}

