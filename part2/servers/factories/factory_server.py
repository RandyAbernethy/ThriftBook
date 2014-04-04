#!/usr/bin/env python

import sys
sys.path.append("gen-py")
from thrift.transport import TTransport
from thrift.transport import TSocket
from thrift.protocol import TJSONProtocol
from thrift.server import TServer
from simple import Message

class MessageHandler(Message.Iface):
    msgs = ["Apache Thrift!!",
            "Childhood is a short season",
            "'Twas brillig"]
    def __init__(self):
        self.msg_index = 0
    def motd(self):
        self.msg_index += 1
        print("Call count: %s" % self.msg_index)
        return MessageHandler.msgs[self.msg_index%3]
 
if __name__ == "__main__": 
    handler = MessageHandler()
    proc = Message.Processor(handler)
    svr_trans = TSocket.TServerSocket(port=8585)
    
    trans_fac = TTransport.TFramedTransportFactory()
    proto_fac = TJSONProtocol.TJSONProtocolFactory()
    
    server = TServer.TThreadedServer(proc, svr_trans, trans_fac, proto_fac)
    server.serve()

