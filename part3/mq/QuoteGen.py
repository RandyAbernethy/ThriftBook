#!/usr/bin/env python
import sys
import pika
import time

sys.path.append("gen-py")
from thrift.transport import TTransport
from thrift.protocol import TCompactProtocol
from trade_report import ttypes

connection = pika.BlockingConnection(
        pika.ConnectionParameters(host='localhost'))
channel = connection.channel()
channel.queue_declare(queue='trade_reports')

trans = TTransport.TMemoryBuffer()
proto = TCompactProtocol.TCompactProtocol(trans)
tr = ttypes.TradeReport()
trans.open()

for seq_num in range(1,20):
    time.sleep(seq_num%4)

    tr.symbol = ["CSCO", "MSFT", "IBM", "VMW", "INTC"][seq_num%5]
    tr.price = 25.50
    tr.size = 500
    tr.seq_num = seq_num

    trans.cstringio_buf.seek(0)
    trans.cstringio_buf.truncate();
    tr.write(proto)
    trans.flush()
    channel.basic_publish(exchange='',
                          routing_key='trade_reports',
                          body=trans.cstringio_buf.getvalue())
    print("Sent trade for " + tr.symbol)

connection.close()


