// Apache Thrift Protocol Comparison in C++ 

#include <iostream>
#include <string>
#include <chrono>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

//Object to serialize
struct Trade {
   char symbol[16];
   double price;
   int size;
};

//Stop watch
template<class T>
class Clock {						
public:
    double precision() {					
        return double(T::period::num) / T::period::den;
    }
    bool isSteady() {					
        return T::is_steady;
    }
    decltype(T::now()) now() {				
        return T::now();
    }
    double elapsed(typename T::time_point start, 
                   typename T::time_point stop) {		
        return std::chrono::duration<double>(stop - start).count();
    }
};

//The protocol/transport stack test driver
//
// Reads two command line arguments
// Arg1 chooses the transport, memory or file (m|f)
// Arg2 chooses the protocol, binary/compact/json (b|c|j)
// example: 
//     proto_write_times f j
// to run the test with a file transport and JSON protocol
int main(int argc, char *argv[]) {
    if (argc != 3) {					
        std::cout << "usage: " << argv[0] 
                  << " (m[emory]|f[file]) (b[inary]|c[ompact]|j[son])" 
         << std::endl;
        return -1;
    }

	//Set the Transport
    boost::shared_ptr<TTransport> trans;			
    if (argv[1][0] == 'm' || argv[1][0] == 'M') {
        const int mem_size = 1024*1024*64;
        trans.reset(new TMemoryBuffer(mem_size));
        std::cout << "Writing memory, buffer size: " << mem_size 
                  << std::endl;
    }
    else if (argv[1][0] == 'f' || argv[1][0] == 'F') {
        const std::string path_name("/tmp/thrift_data");
        trans.reset(new TSimpleFileTransport(path_name, false, true));
        std::cout << "Writing to: " << path_name << std::endl;
    }
    else {
        std::cout << "usage: " << argv[0] 
                  << " (m[emory]|f[file]) (b[inary]|c[ompact]|j[son])" 
                  << std::endl;
        return -1;
    }

	//Set the Protocol
    std::unique_ptr<TProtocol> proto;			
    if (argv[2][0] == 'b' || argv[2][0] == 'B')
        proto.reset(new TBinaryProtocol(trans));
    else if (argv[2][0] == 'c' || argv[2][0] == 'C')
        proto.reset(new TCompactProtocol(trans));
    else if (argv[2][0] == 'j' || argv[2][0] == 'J')
        proto.reset(new TJSONProtocol(trans));
    else {
        std::cout << "usage: " << argv[0] << 
 			" (m[emory]|f[file]) (b[inary]|c[ompact]|j[son])" 
                  << std::endl;
        return -1;
    }

	//Report clock information
    Clock<std::chrono::steady_clock> clock;
    std::cout << "Clock precision in seconds: " << clock.precision() 	
 		  << " (steady: " << clock.isSteady() << ")" << std::endl;

	//Init the object (different values can have an affect on 
	//JSON ad Compact protocol performance !)
    Trade trade;
    trade.symbol[0] = 'F'; trade.symbol[1] = '\0';
    trade.price = 13.10;
    trade.size = 2500;

	//Serialize the object and write to the transport 1mm times
    auto start = clock.now();
    int i = 0;
    for (int loop_count = 0; loop_count < 1000000; ++loop_count) { 
        i += proto->writeStructBegin("Trade");

        i += proto->writeFieldBegin("symbol", 
                                    ::apache::thrift::protocol::T_STRING, 
                                    1);
        i += proto->writeString(std::string(trade.symbol));
        i += proto->writeFieldEnd();

        i += proto->writeFieldBegin("price", 
                                    ::apache::thrift::protocol::T_DOUBLE, 
                                    2);
        i += proto->writeDouble(trade.price);
        i += proto->writeFieldEnd();

        i += proto->writeFieldBegin("size", 
                                    ::apache::thrift::protocol::T_I32, 3);
        i += proto->writeI32(trade.size);
        i += proto->writeFieldEnd();

        i += proto->writeFieldStop();
        i += proto->writeStructEnd();
    }

	//Report the results
    std::cout << "elapsed: " << clock.elapsed(start, clock.now()) 
              << std::endl;
    std::cout << "Wrote " << i << " bytes" << std::endl;
}

