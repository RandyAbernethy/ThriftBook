// Apache Thrift Binary Protocol in Java

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TMemoryBuffer;

public class BinMem {

    public static void main(String[] args) throws TException {
        TMemoryBuffer trans = new TMemoryBuffer(4096);
        TProtocol proto = new TBinaryProtocol(trans);

        proto.writeString("Hello Thrift Serialization");
        System.out.println("Wrote " + trans.length() + " bytes to the TMemoryBuffer");

        String strMsg = proto.readString();
        System.out.println("Recovered string: " + strMsg);
    }
}

