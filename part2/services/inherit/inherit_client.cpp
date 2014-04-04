#include <iostream>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/SocialUpdate.h"					

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   

int main(int argv, char * argc[]) {
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 8585));
    socket->open();
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(socket));
    SocialUpdateClient client(protocol);

    std::string site_name;
    client.GetSiteByRank(site_name, 1);
    std::cout << "Number 1 site: " << site_name <<std::endl;
    std::cout << "Twitter rank : " << client.GetSiteRankByName("Twitter") <<std::endl;  
    std::cout << "Twitter users: " << client.GetSiteUsersByName("Twitter") <<std::endl;  
    client.UpdateSiteUsers("Twitter", 260000000);
    std::cout << "Twitter users: " << client.GetSiteUsersByName("Twitter") <<std::endl;  
}

