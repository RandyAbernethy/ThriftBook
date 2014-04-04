// Apache Thrift Memory Transport Borrow in C++ 

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

    uint32_t len = sizeof(trade);
    Trade * ptrade = (Trade *) transport.borrow(nullptr, &len);
	if (nullptr == ptrade || sizeof(trade) > len) {
		std::cout << "Failed to borrow a complete trade!" << std::endl;
        return -1;
	}

    std::cout << "Trade(" << len << "): " << ptrade->symbol << " " 
 			  << ptrade->size << " @ " << ptrade->price << std::endl;

	transport.consume(sizeof(trade));
}

