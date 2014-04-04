// Apache Thrift Manual Framing Network Transport Client in C++ 

#include <string>
#include <iostream>
#include <memory>
#include <thrift/transport/TSocket.h>

using namespace apache::thrift::transport;

int main(int argv, char **argc)
{
    //Connect to the server
    std::unique_ptr<TTransport> upTrans(new TSocket("localhost", 8585));
    upTrans->open();

    //Send a framed message
    const std::string msg(argc[1]);
    uint32_t frame_size = htonl(msg.length());
    upTrans->write(reinterpret_cast<const uint8_t *>(&frame_size), 4);
    upTrans->write(reinterpret_cast<const uint8_t *>(msg.c_str()), msg.length());
    upTrans->flush();

    //Receive a framed response
    upTrans->read(reinterpret_cast<uint8_t *>(&frame_size), 4);
    frame_size = ntohl(frame_size);
	std::unique_ptr<char[]> upBuf(new char[frame_size+1]);
    int bytes_read = upTrans->read(reinterpret_cast<uint8_t *>(upBuf.get()), frame_size);
    if (frame_size == bytes_read) {
        upBuf[bytes_read] = '\0';
        std::cout << upBuf.get() << std::endl;
    }

    //Cleanup
    upTrans->close();
}

