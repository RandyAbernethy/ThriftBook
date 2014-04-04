// Apache Thrift Server Transport in C++ 

#include <string>
#include <iostream>
#include <memory>
#include <thrift/transport/TServerSocket.h>
#include <boost/shared_ptr.hpp>

using namespace apache::thrift::transport;

int main()
{
    const std::string msg("Hello Thrift!\n");
    const std::string stop_cmd("STOP");
    const int buf_size = 1024*8;
    char buf[buf_size] = "";

    std::unique_ptr<TServerTransport> acceptor(new TServerSocket(8585));
	acceptor->listen();
	std::cout << "[Server] listening on port 8585" << std::endl;

    while (true) {
		boost::shared_ptr<TTransport> trans = acceptor->accept();
		std::cout << "[Server] handling request" << std::endl;
		trans->read(reinterpret_cast<uint8_t *>(buf), buf_size);
        if (0 == stop_cmd.compare(0, std::string::npos, buf, 4))
            break;
		trans->write(reinterpret_cast<const uint8_t *>(msg.c_str()), msg.length());
		trans->flush();
		trans->close();
	}

	std::cout << "[Server] exiting" << std::endl;
    acceptor->close();
}

