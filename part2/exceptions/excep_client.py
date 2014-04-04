# Apache Thrift User Defined Exception Client in Python

import sys
sys.path.append("gen-py")

from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from excep import TradeHistory
from excep.ttypes import BadFish

socket = TSocket.TSocket("localhost", 8585)
socket.open()
protocol = TBinaryProtocol.TBinaryProtocol(socket)
client = TradeHistory.Client(protocol)
try:
    print("[Client] received: %f" % client.GetLastSale(sys.argv[1]))
except BadFish as bf:
    print("[Client] GetLastSale() call failed for fish: %s, error %d" % (bf.fish, bf.error_code))

