# Apache Thrift User Defined Exception Client in Python

import sys
sys.path.append("gen-py")

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from excep import TradeHistory
from excep.ttypes import BadFish

trans = TSocket.TSocket("localhost", 9090)
trans = TTransport.TBufferedTransport(trans)
proto = TBinaryProtocol.TBinaryProtocol(trans)
client = TradeHistory.Client(proto)

try:
    trans.open()
    print("[Client] received: %f" % client.GetLastSale(sys.argv[1]))
except BadFish as bf:
    print("[Client] GetLastSale() call failed for fish: %s, error %d" % (bf.fish, bf.error_code))

trans.close()
