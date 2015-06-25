# Apache Thrift Network Transport Client in Python

import sys

from thrift.transport import TSocket			
from thrift.transport import TTransport			

trans = TSocket.TSocket("localhost", 9090)
trans.open()
trans.write(sys.argv[1])
trans.flush()
data = trans.read(4096)
if len(data) > 0:
    print("[Client] received: " + data)  
trans.close()

