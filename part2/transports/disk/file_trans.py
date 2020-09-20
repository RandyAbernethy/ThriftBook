# Apache Thrift File Transport in Python

import pickle
from thrift.transport import TTransport

class Trade:
    def __init__(self, symbol="", price=0.0, size=0):
        self.symbol=symbol
        self.price=price
        self.size=size

trans_out = TTransport.TFileObjectTransport(open("data","wb"))
trade = Trade("F", 13.10, 2500)
trans_out.write(pickle.dumps(trade));
trans_out.close()

trans_in = TTransport.TFileObjectTransport(open("data","rb"))
bstr = trans_in.read(4096)
trade = pickle.loads(bstr)
print("Trade(%d): %s %d @ %f" % (len(bstr), trade.symbol, trade.size, trade.price))

