# Apache Thrift Binary Protocol in Python

from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

trans = TTransport.TMemoryBuffer()
proto = TBinaryProtocol.TBinaryProtocol(trans)
proto.writeString("Hello Thrift Serialization")
print ("Wrote %d bytes to the TMemoryBuffer" % (trans.cstringio_buf.tell()))

trans.cstringio_buf.seek(0)
msg = proto.readString()
print("Recovered string: %s" % (msg))

