# Apache Thrift Binary Protocol Struct 2.0 Writer in Python

from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift import Thrift

class Trade:
    def __init__(self):
        symbol=""
        price=0.0
        size=0
        timestamp=0.0				

trans = TTransport.TFileObjectTransport(open("data","wb"))
proto = TBinaryProtocol.TBinaryProtocol(trans)

trade = Trade()
trade.symbol = "GE"
trade.price = 27.25
trade.size = 1700
trade.timestamp = 9.5

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

proto.writeFieldBegin("timestamp", Thrift.TType.DOUBLE, 4)	
proto.writeDouble(trade.timestamp)
proto.writeFieldEnd()

proto.writeFieldStop()
proto.writeStructEnd()
        
print("Wrote Trade: %s %d @ %f  tm: %f" % 
      (trade.symbol, trade.size, trade.price, trade.timestamp))

