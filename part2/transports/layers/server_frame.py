# Apache Thrift Frame Layer Network Transport Server in Python

from thrift.transport import TSocket
from thrift.transport import TTransport

acceptor = TSocket.TServerSocket(port=9090)
acceptor.listen();
print("[Server] listening on port 9090")

while (True):
    trans_ep = acceptor.accept();
    trans = TTransport.TFramedTransport(trans_ep)
    data = trans.read(1024*8)
    print("[Server] handling request: %s" % (data))
    trans.write("Hello Thrift!");
    trans.flush()
    trans.close() 
    if data[:4] == "STOP":
        break

print("[Server] exiting")
acceptor.close()

