#!/usr/bin/env python
import sys
import pika

sys.path.append("gen-py")
from thrift.transport import TTransport
from thrift.protocol import TCompactProtocol
from trade_report import ttypes

def callback(ch, method, properties, body):
    trans = TTransport.TMemoryBuffer(body)
    proto = TCompactProtocol.TCompactProtocol(trans)
    tr = ttypes.TradeReport()
    trans.open()
    tr.read(proto)
    trans.close()
    print("[" + str(tr.seq_num) + "] " + tr.symbol + 
            " @ " + str(tr.price) + " x " + str(tr.size))

connection = pika.BlockingConnection(
        pika.ConnectionParameters(host='localhost'))
channel = connection.channel()
channel.queue_declare(queue='trade_reports')
print 'Waiting for trade reports...'
channel.basic_consume(callback,
                      queue='trade_reports',
                      no_ack=True)
channel.start_consuming()
