# Apache Thrift JSON Protocol Struct Writer in Python 

from thrift.transport import TTransport
from thrift.protocol import TJSONProtocol
from thrift import Thrift

class Trade:
    def __init__(self, symbol="", price=0.0, size=0):
        self.symbol=symbol
        self.price=price
        self.size=size

trans = TTransport.TFileObjectTransport(open("data.json","wb"))
proto = TJSONProtocol.TJSONProtocol(trans)					

trade = Trade("F", 13.10, 2500)

proto.writeStructBegin("Trade")

proto.writeFieldBegin("symbol", Thrift.TType.STRING, 1)
proto.writeString(trade.symbol)
proto.writeFieldEnd()

proto.writeFieldBegin("price", Thrift.TType.DOUBLE, 2)
proto.writeDouble(trade.price)
proto.writeFieldEnd()

proto.writeFieldBegin("size", Thrift.TType.I32, 3)
proto.writeI32(trade.size)
proto.writeFieldEnd()

proto.writeFieldStop()
proto.writeStructEnd()
        
print("Wrote Trade: %s %d @ %f" % (trade.symbol, trade.size, trade.price))

