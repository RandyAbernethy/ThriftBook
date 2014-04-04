# Apache Thrift Network Transport in Python

from thrift.transport import TSocket			
from thrift.transport import TTransport			

def read_trans(t):					
    while (True):
        try:
            data = t.read(4096)
            if len(data) > 0:
                print(data)  
            else:
                break
        except:
            break

#read network
trans = TSocket.TSocket("thrift.apache.org", 80)
trans.open()
trans.write("GET /\n")
trans.flush()
read_trans(trans)
trans.close()
#Read file
trans = TTransport.TFileObjectTransport(open("sock_trans.py","rb"))
trans.open()
read_trans(trans)
trans.close()

