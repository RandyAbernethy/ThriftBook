import logging
logging.basicConfig()
import sys
sys.path.append("gen-py")

from thrift.transport import TTransport
from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from thrift.server import TProcessPoolServer
from hello_name import HelloSvc

class HelloHandler:
    def hello_func(self, fname, lname):
        print("[Server] Handling client request")
        return "Hello " + fname + " " + lname

handler = HelloHandler()
proc = HelloSvc.Processor(handler)
trans_ep = TSocket.TServerSocket(port=9095)
trans_fac = TTransport.TBufferedTransportFactory()
proto_fac = TBinaryProtocol.TBinaryProtocolFactory()
server = TProcessPoolServer.TProcessPoolServer(proc, trans_ep, trans_fac, proto_fac)

print("[Server] Started")
server.serve()

