// Apache Thrift Compact Protocol Struct Writer in Java 

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.protocol.TCompactProtocol;
import org.apache.thrift.protocol.TField;
import org.apache.thrift.protocol.TStruct;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TSimpleFileTransport;
import org.apache.thrift.protocol.TType;

public class CompFileWrite {

    static private class Trade {
        public String symbol;
        public double price;
        public int size;
    };

    public static void main(String[] args) throws TException {
        TTransport trans = new TSimpleFileTransport("/tmp/thrift_data", false, true);
        TProtocol proto = new TCompactProtocol(trans);			

        Trade trade = new Trade();
        trade.symbol = "F";
        trade.price = 13.10;
        trade.size = 2500;

        proto.writeStructBegin(new TStruct());

        proto.writeFieldBegin(new TField("symbol", 
                                         TType.STRING, 
                                         (short) 1));
        proto.writeString(trade.symbol);
        proto.writeFieldEnd();

        proto.writeFieldBegin(new TField("price", 
                                         TType.DOUBLE, 
                                         (short) 2));
        proto.writeDouble(trade.price);
        proto.writeFieldEnd();

        proto.writeFieldBegin(new TField("size", 
                                         TType.I32, 
                                         (short) 3));
        proto.writeI32(trade.size);
        proto.writeFieldEnd();

        proto.writeFieldStop();
        proto.writeStructEnd();
        
        System.out.println("Wrote trade to file");
    }
}

