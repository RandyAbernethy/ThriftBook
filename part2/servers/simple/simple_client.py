#!/usr/bin/env python

import sys
sys.path.append("gen-py")
from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from simple import Message

trans = TSocket.TSocket("localhost", 8585)
trans.open()
proto = TBinaryProtocol.TBinaryProtocol(trans)
client = Message.Client(proto)

while True:
    print("[Client] received: %s" % client.motd())
    line = raw_input("Enter 'q' to exit, anything else to continue: ")
    if line == 'q':
        break
        
trans.close()  
