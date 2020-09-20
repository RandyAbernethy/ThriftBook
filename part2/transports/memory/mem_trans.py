# Apache Thrift Memory Transport in Python 

import pickle
from thrift.transport import TTransport

class Trade:
    def __init__(self, symbol="", price=0.0, size=0):
        self.symbol=symbol
        self.price=price
        self.size=size

trans = TTransport.TMemoryBuffer()
trade = Trade("F", 13.10, 2500)
trans.write(pickle.dumps(trade))

trans.cstringio_buf.seek(0)
bstr = trans.read(4096)
trade_read = pickle.loads(bstr)
print("Trade(%d): %s %d @ %f" % (len(bstr), trade_read.symbol, trade_read.size, trade_read.price))

