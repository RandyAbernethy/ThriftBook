// Apache Thrift Memory Transport in Java 

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import org.apache.thrift.transport.TMemoryBuffer;
import org.apache.thrift.transport.TTransportException;

public class MemTrans {

    static private class Trade implements Serializable {
        public String symbol;
        public double price;
        public int size;
    };

    public static void main(String[] args) 
            throws IOException, TTransportException, ClassNotFoundException {
        TMemoryBuffer transport = new TMemoryBuffer(4096);

        Trade trade = new Trade();
        trade.symbol = "F";
        trade.price = 13.10;
        trade.size = 2500;
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(baos);
        oos.writeObject(trade);
        transport.write(baos.toByteArray());

        byte[] buf = new byte[128];
        int bytes_read = transport.read(buf, 0, buf.length);
        ByteArrayInputStream bais = new ByteArrayInputStream(buf);
        ObjectInputStream ois = new ObjectInputStream(bais);
        Trade trade_read = (Trade) ois.readObject();
        System.out.println("Trade(" + bytes_read + "): " + trade_read.symbol
                + " " + trade_read.size + " @ " + trade_read.price);
    }
}

