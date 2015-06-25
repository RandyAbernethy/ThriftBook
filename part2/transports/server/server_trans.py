# Apache Thrift Server Transport in Python

from thrift.transport import TSocket

acceptor = TSocket.TServerSocket(port=9090)
acceptor.listen();
print("[Server] listening on port 9090")

while (True):
    trans = acceptor.accept();
    data = trans.read(1024*8)
    print("[Server] handling request: " + data)
    trans.write("Hello Thrift!");
    trans.flush()
    trans.close() 
    if data[:4] == "STOP":
        break

print("[Server] exiting")
acceptor.close()

