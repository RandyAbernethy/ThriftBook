// Apache Thrift Binary Protocol in C++ 

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

using namespace apache::thrift::transport;

int main()
{
    boost::shared_ptr<TTransport> trans(new TMemoryBuffer(4096));
    apache::thrift::protocol::TBinaryProtocol proto(trans);

    int i = proto.writeString(std::string("Hello Thrift Serialization"));
    std::cout << "Wrote " << i << " bytes to the TMemoryBuffer" << std::endl;

    std::string msg;
    i = proto.readString(msg);
    std::cout << "Read " << i << " bytes from the TMemoryBuffer" << std::endl;
    std::cout << "Recovered string: " << msg << std::endl;
}

