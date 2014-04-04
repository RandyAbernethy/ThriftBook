// Apache Thrift File Transport in Java

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import org.apache.thrift.transport.TSimpleFileTransport;
import org.apache.thrift.transport.TTransportException;

public class FileTrans {

    static private class Trade implements Serializable {	
        public String symbol;
        public double price;
        public int size;
    };

    public static void main(String[] args) 
            throws IOException, TTransportException, ClassNotFoundException {
        Trade trade = new Trade();
        trade.symbol = "F";
        trade.price = 13.10;
        trade.size = 2500;

        TSimpleFileTransport trans_out = new TSimpleFileTransport("data",false,true);	
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(baos);
        oos.writeObject(trade);
        trans_out.write(baos.toByteArray());				
        trans_out.close();				

        TSimpleFileTransport trans_in = new TSimpleFileTransport("data",true,false);
        byte[] buf = new byte[128];
        int iBytesRead = trans_in.read(buf, 0, buf.length);		
        ByteArrayInputStream bais = new ByteArrayInputStream(buf);
        ObjectInputStream ois = new ObjectInputStream(bais);
        trade = (Trade) ois.readObject();

        System.out.println("Trade(" + iBytesRead + "): " + trade.symbol
                + " " + trade.size + " @ " + trade.price);
    }
}

