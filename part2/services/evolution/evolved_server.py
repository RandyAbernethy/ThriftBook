import sys
sys.path.append('gen-py')

from thrift.transport import TSocket
from thrift.server import TServer
from evolved import SocialLookup

site_rank = {1 : ("Facebook", 750000000),
             2 : ("Twitter",  250000000),
             3 : ("LinkedIn", 110000000) }

class SocialLookupHandler(SocialLookup.Iface):
    def GetSiteByRank(self, rank):
        tup = site_rank[rank]
        return "" if (None==tup) else tup[0]

    def GetSiteRankByName(self, name, allowPartialMatch):
        for rank, value in site_rank.items():
            if allowPartialMatch:
                if value[0][:len(name)] == name:
                    return rank
            else:
                if value[0] == name:
                    return rank
        return 0

    def GetSitesByUsers(self, minUserCount, maxUserCount):
        return [v[0] for k, v in site_rank.items() 
                if v[1] >= minUserCount and v[1] <= maxUserCount]

if __name__ == "__main__": 
    trans_svr = TSocket.TServerSocket(port=9090)
    proc = SocialLookup.Processor(SocialLookupHandler())
    server = TServer.TSimpleServer(proc, trans_svr)
    server.serve()

