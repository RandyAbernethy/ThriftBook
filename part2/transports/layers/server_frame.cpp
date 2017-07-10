// Apache Thrift Frame Layer Network Transport Server in C++ 

#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <string>
#include <iostream>
#include <memory>

using namespace apache::thrift::transport;
using boost::shared_ptr;
using boost::make_shared;

int main()
{
    const std::string msg("Hello Thrift!\n");
    const std::string stop_cmd("STOP");
    const int buf_size = 1024*8;
    char buf[buf_size] = "";
    auto port = 9090;

    auto acceptor = std::make_shared<TServerSocket>(port);
    acceptor->listen();
    std::cout << "[Server] listening on port " << port << std::endl;

    do {
        auto trans_ep = acceptor->accept();
        auto trans = make_shared<TFramedTransport>(trans_ep);
        auto len = trans->read(reinterpret_cast<uint8_t *>(buf), buf_size);
        buf[(0 < len && len < buf_size) ? len : 0] = '\0';
        std::cout << "[Server] handling request: " << buf << std::endl;
        trans->write(reinterpret_cast<const uint8_t *>(msg.c_str()), msg.length());
        trans->flush();
        trans->close();
    } while (0 == stop_cmd.compare(0, std::string::npos, buf, 4));

    std::cout << "[Server] exiting" << std::endl;
    acceptor->close();
}

