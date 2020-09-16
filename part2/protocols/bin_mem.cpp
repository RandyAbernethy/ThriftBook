// Apache Thrift Binary Protocol in C++ 

#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <memory>
#include <iostream>
#include <string>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using std::make_shared;

int main()
{
    auto trans = make_shared<TMemoryBuffer>(4096);
    TBinaryProtocol proto(trans);

    int i = proto.writeString(std::string("Hello Thrift Serialization"));
    std::cout << "Wrote " << i << " bytes to the TMemoryBuffer" << std::endl;

    std::string msg;
    i = proto.readString(msg);
    std::cout << "Read " << i << " bytes from the TMemoryBuffer" << std::endl;
    std::cout << "Recovered string: " << msg << std::endl;
}

