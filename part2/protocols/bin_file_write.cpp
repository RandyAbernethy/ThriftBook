// Apache Thrift Binary Protocol Struct Writer in C++ 

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

struct Trade {
   char symbol [16];
   double price;
   int size;
};

int main()
{
    Trade trade;
    trade.symbol [0] = 'F'; trade.symbol[1] = '\0';
    trade.price = 13.10;
    trade.size = 2500;

    const std::string path_name("data");
    boost::shared_ptr<TTransport> trans =
        boost::make_shared<TSimpleFileTransport>(path_name, false, true);
    boost::shared_ptr<TProtocol> proto =
        boost::make_shared<TBinaryProtocol>(trans);

    int i = 0;
    i += proto->writeStructBegin("Trade");

    i += proto->writeFieldBegin("symbol ",
                               ::apache::thrift::protocol::T_STRING, 1);
    i += proto->writeString(std::string(trade.symbol));
    i += proto->writeFieldEnd();

    i += proto->writeFieldBegin("price ",
                               ::apache::thrift::protocol::T_DOUBLE, 2);
    i += proto->writeDouble(trade.price);
    i += proto->writeFieldEnd();

    i += proto->writeFieldBegin("size ", ::apache::thrift::protocol::T_I32, 3);
    i += proto->writeI32(trade.size);
    i += proto->writeFieldEnd();

    i += proto->writeFieldStop();
    i += proto->writeStructEnd();

    std::cout << "Wrote " << i << " bytes to " << path_name << std::endl;
}

