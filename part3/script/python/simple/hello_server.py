# Apache Thrift Hello World Python Server

import sys
sys.path.append("gen-py")

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer
from hello import helloSvc

class HelloHandler(helloSvc.Iface):
    def getMessage(self, name):
        print("[Server] Handling client request: " + name)
        return "Hello " + name

handler = HelloHandler()
proc = helloSvc.Processor(handler)
trans_svr = TSocket.TServerSocket(port=9090)
trans_fac = TTransport.TBufferedTransportFactory()
proto_fac = TBinaryProtocol.TBinaryProtocolFactory()
server = TServer.TSimpleServer(proc, trans_svr, trans_fac, proto_fac)

print("[Server] Started")
server.serve()

