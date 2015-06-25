import sys
sys.path.append("gen-py")

from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from evolved import SocialLookup

trans = TSocket.TSocket("localhost", 9090)
proto = TBinaryProtocol.TBinaryProtocol(trans)
client = SocialLookup.Client(proto)

trans.open()
print("Number 1 site: %s" % (client.GetSiteByRank(1)))
print("Twitter rank : %d" % (client.GetSiteRankByName("Twit", True)))
print("Range 1-5 hm : %s" % (str(client.GetSitesByUsers(100000000, 500000000))))
trans.close()

