# Apache Thrift Frame Layer Network Transport Server in Python

from thrift.transport import TSocket
from thrift.transport import TTransport

acceptor = TSocket.TServerSocket(port=8585)
acceptor.listen();
print("[Server] listening on port 8585")

while (True):
    ep_trans = acceptor.accept();
    trans = TTransport.TFramedTransport(ep_trans)
    print("[Server] handling request")
    data = trans.read(1024*8)
    if data[:4] == "STOP":
        break
    trans.write("Hello Thrift!");
    trans.flush()
    trans.close() 

print("[Server] exiting")
acceptor.close()

