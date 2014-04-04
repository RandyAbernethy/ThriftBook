import sys
sys.path.append("gen-py")
from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from evolved import SocialLookup

socket = TSocket.TSocket("localhost", 8585)
socket.open()
protocol = TBinaryProtocol.TBinaryProtocol(socket)
client = SocialLookup.Client(protocol)
print("Number 1 site: %s" % (client.GetSiteByRank(1)))
print("Twitter rank : %d" % (client.GetSiteRankByName("Twit", True)))
print("Twitter rank : %s" % (str(client.GetSitesByUsers(100000000, 500000000))))

