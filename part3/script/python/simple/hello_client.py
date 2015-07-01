# Apache Thrift Hello World Python Client

import sys
sys.path.append("gen-py")
from hello import helloSvc

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

trans = TSocket.TSocket("localhost", 9090)
trans = TTransport.TBufferedTransport(trans)
proto = TBinaryProtocol.TBinaryProtocol(trans)
client = helloSvc.Client(proto)

trans.open()
msg = client.getMessage("world")
print("[Client] received: %s" % msg)
trans.close()
