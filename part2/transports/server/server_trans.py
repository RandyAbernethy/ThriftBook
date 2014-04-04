# Apache Thrift Server Transport in Python

from thrift.transport import TSocket

acceptor = TSocket.TServerSocket(port=8585)
acceptor.listen();
print("[Server] listening on port 8585")

while (True):
    trans = acceptor.accept();
    print("[Server] handling request")
    data = trans.read(1024*8)
    if data[:4] == "STOP":
        break
    trans.write("Hello Thrift!");
    trans.flush()
    trans.close() 

print("[Server] exiting")
acceptor.close()

