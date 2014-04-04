// Apache Thrift File Transport in C++ 

#include <iostream>
#include <cstring>
#include <thrift/transport/TSimpleFileTransport.h>

using namespace apache::thrift::transport;	

struct Trade {		
   char symbol[16];
   double price;
   int size;
};

int main() {
    TSimpleFileTransport trans_out("data", false, true);	
    Trade trade;
    trade.symbol[0] = 'F'; trade.symbol[1] = '\0';
    trade.price = 13.10;
    trade.size = 2500;
    trans_out.write((const uint8_t *)&trade, sizeof(trade));
    trans_out.close();					

    TSimpleFileTransport trans_in("data", true, false);	
    std::memset(&trade, 0, sizeof(trade));
    int bytes_read = trans_in.read((uint8_t *)&trade, sizeof(trade));

    std::cout << "Trade(" << bytes_read << "): " << trade.symbol 
              << " " << trade.size << " @ " << trade.price 
              << std::endl;
}

