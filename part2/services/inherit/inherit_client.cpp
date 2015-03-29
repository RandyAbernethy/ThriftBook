#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/SocialUpdate.h"					

using namespace apache::thrift::transport;  
using namespace apache::thrift::protocol;   

int main() {
    boost::shared_ptr<TTransport> trans;
    trans = boost::make_shared<TSocket>("localhost", 8585);
    trans = boost::make_shared<TBufferedTransport>(trans);
    trans->open();

    auto proto = boost::make_shared<TBinaryProtocol>(trans);
    SocialUpdateClient client(proto);

    std::string site_name;
    client.GetSiteByRank(site_name, 1);
    std::cout << "Number 1 site: " << site_name <<std::endl;
    std::cout << "Twitter rank : " << client.GetSiteRankByName("Twitter") <<std::endl;  
    std::cout << "Twitter users: " << client.GetSiteUsersByName("Twitter") <<std::endl;  
    client.UpdateSiteUsers("Twitter", 260000000);
    std::cout << "Twitter users: " << client.GetSiteUsersByName("Twitter") <<std::endl;  
}

