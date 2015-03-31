# Apache Thrift Hello World Python Client

import sys
sys.path.append("gen-py")

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from hello import HelloSvc

trans = TSocket.TSocket("localhost", 9095)
trans = TTransport.TBufferedTransport(trans)
proto = TBinaryProtocol.TBinaryProtocol(trans)
client = HelloSvc.Client(proto)

trans_ep.open()
msg = client.hello_func()
print("[Client] received: %s" % msg)
