import sys
sys.path.append('gen-py')

from hello import helloSvc
from thrift.protocol import TJSONProtocol
from thrift.server import THttpServer

class HelloSvcHandler:
  def getMessage(self, name):
    print "Called with " + name
    return "hello " + name

processor = helloSvc.Processor(HelloSvcHandler())
protoFactory = TJSONProtocol.TJSONProtocolFactory()
port = 9090
server = THttpServer.THttpServer(processor, ("localhost", port), protoFactory)
print "Python server running on port " + str(port)
server.serve()

