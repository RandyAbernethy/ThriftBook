#include "gen-cpp/SocialUpdate.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <memory>
#include <iostream>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using std::make_shared;
using std::shared_ptr;

int main() {
    shared_ptr<TTransport> trans;
    trans = make_shared<TSocket>("localhost", 9090);
    trans = make_shared<TBufferedTransport>(trans);
    auto proto = make_shared<TBinaryProtocol>(trans);
    SocialUpdateClient client(proto);

    trans->open();
    std::string site_name;
    client.GetSiteByRank(site_name, 1);
    std::cout << "Number 1 site: " << site_name <<std::endl;
    std::cout << "Twitter rank : " << client.GetSiteRankByName("Twitter") <<std::endl;  
    std::cout << "Twitter users: " << client.GetSiteUsersByName("Twitter") <<std::endl;  
    client.UpdateSiteUsers("Twitter", 260000000);
    std::cout << "Twitter users: " << client.GetSiteUsersByName("Twitter") <<std::endl;  
    trans->close();
}

