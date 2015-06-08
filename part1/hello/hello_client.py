# Apache Thrift Hello World Python Client

import sys
sys.path.append("gen-py")
from hello import HelloSvc

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

trans = TSocket.TSocket("localhost", 9095)
trans = TTransport.TBufferedTransport(trans)
proto = TBinaryProtocol.TBinaryProtocol(trans)
client = HelloSvc.Client(proto)

trans.open()
msg = client.hello_func()
print("[Client] received: %s" % msg)
