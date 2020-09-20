# Apache Thrift File Transport in Python

import pickle
from thrift.transport import TTransport

class Trade:
    def __init__(self, symbol, price, size):
        self.symbol=""
        self.price=0.0
        self.size=0

trans_out = TTransport.TFileObjectTransport(open("data","wb"))
trade = Trade("F", 13.10, 2500)
trans_out.write(pickle.dumps(trade));
trans_out.close()

trans_in = TTransport.TFileObjectTransport(open("data","rb"))
bstr = trans_in.read(4096)
trade = pickle.loads(bstr)
print("Trade(%d): %s %d @ %f" % (len(bstr), trade.symbol, trade.size, trade.price))

