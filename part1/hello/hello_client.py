# Apache Thrift Hello World Python Client

import sys
sys.path.append("gen-py")

from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from hello import HelloSvc

socket = TSocket.TSocket("localhost", 8585)
socket.open()
protocol = TBinaryProtocol.TBinaryProtocol(socket)

client = HelloSvc.Client(protocol)
msg = client.hello_func()
print("[Client] received: %s" % msg)
