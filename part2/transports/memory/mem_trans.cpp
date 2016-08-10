// Apache Thrift Memory Transport in C++ 

#include <thrift/transport/TBufferTransports.h>
#include <iostream>

struct Trade {
   char symbol[16];
   double price;
   int size;
};

int main() {
    apache::thrift::transport::TMemoryBuffer trans(4096);

    Trade t{"F", 13.10, 2500};
    trans.write(reinterpret_cast<const uint8_t *>(&t), sizeof(t));

    Trade tin;
    int n = trans.read(reinterpret_cast<uint8_t *>(&tin), sizeof(tin));

    std::cout << "Trade(" << n << "): " << tin.symbol << " "
              << tin.size << " @ " << tin.price << std::endl;
}

