// Apache Thrift Manual Framing Network Transport Client in C++ 

#include <thrift/transport/TSocket.h>
#include <string>
#include <iostream>
#include <memory>

using namespace apache::thrift::transport;

int main(int argv, char **argc)
{
    //Connect to the server
    auto trans = std::make_shared<TSocket>("localhost", 9090);
    trans->open();

    //Send a framed message
    const std::string msg = (argv >1) ? argc[1] : "Test";
    uint32_t frame_size = htonl(msg.length());
    trans->write(reinterpret_cast<const uint8_t *>(&frame_size), 4);
    trans->write(reinterpret_cast<const uint8_t *>(msg.c_str()), msg.length());
    trans->flush();

    //Receive a framed response
    trans->read(reinterpret_cast<uint8_t *>(&frame_size), 4);
    frame_size = ntohl(frame_size);
    std::unique_ptr<char[]> buf(new char[frame_size+1]);
    auto bytes_read = trans->read(reinterpret_cast<uint8_t *>(buf.get()), frame_size);
    if (frame_size == bytes_read) {
        buf[bytes_read] = '\0';
        std::cout << "[Client] " << buf.get() << std::endl;
    } else {
        std::cout << "[Client] Error: Bad Frame Size!!" << std::endl;
    }

    //Cleanup
    trans->close();
}

