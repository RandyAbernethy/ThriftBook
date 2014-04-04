#!/usr/bin/env python

import sys
sys.path.append("gen-py")
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TJSONProtocol
from simple import Message

ep_trans = TSocket.TSocket("localhost", 8585)
ep_trans.open()
trans = TTransport.TFramedTransport(ep_trans)
proto = TJSONProtocol.TJSONProtocol(trans)
client = Message.Client(proto)

while True:
    print("[Client] received: %s" % client.motd())
    line = raw_input("Enter 'q' to exit, anything else to continue: ")
    if line == 'q':
        break
        
ep_trans.close()  
