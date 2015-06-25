// Apache Thrift Network Transport in C++ 

#include <thrift/transport/TSocket.h>			
#include <thrift/transport/TSimpleFileTransport.h>	
#include <memory>
#include <iostream>

using namespace apache::thrift::transport;

void read_trans(TTransport * trans) {	
    const int buf_size = 1024*8;
    char buf[buf_size];

    while (true) {
        int bytes_read = trans->read(reinterpret_cast<uint8_t *>(buf), buf_size-1);
        if (bytes_read <= 0 || buf_size <= bytes_read)
            break;
        buf[bytes_read] = '\0';
        std::cout << buf << std::endl;
    } 
}

int main()
{
    //Display web page
    std::unique_ptr<TTransport> trans(new TSocket("thrift.apache.org",80));			
    trans->open();     							                     
    trans->write(reinterpret_cast<const uint8_t *>("GET / \n"),7);	
    trans->flush();                           				
    read_trans(trans.get());
    trans->close();       						
    //Display file
    trans.reset(new TSimpleFileTransport("sock_trans.cpp"));  		
    trans->open();                            				
    read_trans(trans.get());							
    trans->close();       
}

