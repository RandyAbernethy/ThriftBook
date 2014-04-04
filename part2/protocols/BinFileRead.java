// Apache Thrift Binary Protocol Struct Reader in Java

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TField;
import org.apache.thrift.protocol.TStruct;
import org.apache.thrift.protocol.TType;
import org.apache.thrift.protocol.TProtocolUtil;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TSimpleFileTransport;

public class BinFileRead {

    static private class Trade {
        public String symbol;
        public double price;
        public int size;
    };

    public static void main(String[] args) throws TException {
        TTransport trans = new TSimpleFileTransport("data", true, false);
        TProtocol proto = new TBinaryProtocol(trans);		

        Trade trade_read = new Trade();
        TField field = new TField();

        TStruct struct_obj = proto.readStructBegin();		
        while(true) {						
            field = proto.readFieldBegin();			
            if (field.id == TType.STOP) {				
                break;
            }
            switch(field.id) {					
            case 1:
                trade_read.symbol = proto.readString();	
                break;
            case 2:
                trade_read.price = proto.readDouble();
                break;
            case 3:
                trade_read.size = proto.readI32();
                break;
            default:
                TProtocolUtil.skip(proto,field.type);	
                break;
            }
            proto.readFieldEnd();				
        }
        proto.readStructEnd();				

        System.out.println("Trade: " + trade_read.symbol + " " +
                           trade_read.size + " @ " + trade_read.price);
    }
}


