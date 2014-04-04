# Apache Thrift Hello World Python Server

import sys
sys.path.append("gen-py")

from thrift.transport import TSocket
from thrift.server import TServer
from hello import HelloSvc

class HelloHandler:
    def hello_func(self):
        print("[Server] Handling client request")
        return "Hello thrift, from the python server"

handler = HelloHandler()
processor = HelloSvc.Processor(handler)
listeningSocket = TSocket.TServerSocket(port=8585)
server = TServer.TSimpleServer(processor, listeningSocket)

print("[Server] Started")
server.serve()

