#!/usr/bin/env python

import sys
sys.path.append("gen-py")
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TJSONProtocol
from simple import Message

trans_ep = TSocket.TSocket("localhost", 9090)
trans = TTransport.TFramedTransport(trans_ep)
proto = TJSONProtocol.TJSONProtocol(trans)
client = Message.Client(proto)

trans.open()
while True:
    print("[Client] received: %s" % client.motd())
    line = raw_input("Enter 'q' to exit, anything else to continue: ")
    if line == 'q':
        break

trans.close()
