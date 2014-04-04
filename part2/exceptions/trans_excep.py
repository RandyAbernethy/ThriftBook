# Apache Thrift Transport Exceptions in Python

import pickle
import sys
from thrift import Thrift
from thrift.transport import TTransport

class Trade:
    def __init__(self):
        symbol=""
        price=0.0
        size=0

try:
    trans = TTransport.TFileObjectTransport(open("data","wb"))
    trade = Trade()
    trade.symbol = "F"
    trade.price = 13.10
    trade.size = 2500
    trans.write(pickle.dumps(trade));
    trans.close()

    if len(sys.argv) == 2:						
        raise TTransport.TTransportException(
                  TTransport.TTransportException.NOT_OPEN, "cmd line ex")

    trans = TTransport.TFileObjectTransport(open("data", 		
                                    ("wb" if len(sys.argv) > 2 else "rb")))
    bstr = trans.read(128)
    trade = pickle.loads(bstr)
    print("Trade(%d): %s %d @ %f" % (len(bstr), trade.symbol,
                                     trade.size, trade.price))

except TTransport.TTransportException as tte:			
    print("TTransportException(%d): %s" % (tte.type, tte))
except Thrift.TException as te:					
    print("TException: %s" % te)
except Exception as e:						
    print("Exception: %s %s" % (type(e), e))
except:								
    print("BaseException: %s" % sys.exc_info()[0])

