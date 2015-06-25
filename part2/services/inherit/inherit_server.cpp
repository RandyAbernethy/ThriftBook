#include "gen-cpp/SocialUpdate.h"
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/TProcessor.h>
#include <boost/make_shared.hpp>
#include <string>
#include <unordered_map>

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using boost::make_shared;

struct Site { std::string name; int users; };
std::unordered_map<int, Site> siteRank = { 
    {1, {"Facebook", 750000000}}, 
    {2, {"Twitter",  250000000}}, 
    {3, {"LinkedIn", 110000000}}
};

class SocialUpdateHandler : public SocialUpdateIf {	
public:
    //SocialUpdateIf
    virtual void UpdateSiteUsers(const std::string& name, const int32_t users) override {			
        for (auto & it : siteRank)
            if (0 == it.second.name.compare(name))
                it.second.users = users;
    }
    virtual int32_t GetSiteUsersByName(const std::string& name) override {
        for (auto it : siteRank)
            if (0 == it.second.name.compare(name))
                return it.second.users;
        return 0;
    }
    //SocialLookupIf
    virtual void GetSiteByRank(std::string& _return, const int32_t rank) override {
        auto it = siteRank.find(rank);
        _return = (it == std::end(siteRank)) ? "" : it->second.name;
    }
    virtual int32_t GetSiteRankByName(const std::string& name) override {
        for (auto it : siteRank)
            if (0 == it.second.name.compare(name))
                return it.first;
        return 0;
    }
};

int main(int argc, char **argv) {
  auto handler = make_shared<SocialUpdateHandler>();
  auto proc = make_shared<SocialUpdateProcessor>(handler);
  auto trans_svr = make_shared<TServerSocket>(9090);
  auto trans_fac = make_shared<TBufferedTransportFactory>();
  auto proto_fac = make_shared<TBinaryProtocolFactory>();
  TSimpleServer server(proc, trans_svr, trans_fac, proto_fac);
  server.serve();
  return 0;
}

