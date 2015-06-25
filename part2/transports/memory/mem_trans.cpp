// Apache Thrift Memory Transport in C++ 

#include <thrift/transport/TBufferTransports.h>
#include <iostream>

struct Trade {
   char symbol[16];
   double price;
   int size;
};

int main() {
    apache::thrift::transport::TMemoryBuffer transport(4096);

    Trade trade{"F", 13.10, 2500};
    transport.write(reinterpret_cast<const uint8_t *>(&trade), sizeof(trade));

    Trade trade_read;
    int bytes_read = transport.read(reinterpret_cast<uint8_t *>(&trade_read), sizeof(trade_read));

    std::cout << "Trade(" << bytes_read << "): " << trade_read.symbol << " " 
 			  << trade_read.size << " @ " << trade_read.price << std::endl;
}

