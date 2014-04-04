// Apache Thrift Transport Exceptions in Java

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import org.apache.thrift.TException;
import org.apache.thrift.transport.TSimpleFileTransport;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;

public class TransExcep {

    static private class Trade implements Serializable {
        public String symbol;
        public double price;
        public int size;
    };

    public static void main(String[] args) {
        try {
            TTransport trans = new TSimpleFileTransport("data", false, true);
            Trade trade = new Trade();
            trade.symbol = "F";
            trade.price = 13.10;
            trade.size = 2500;
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(trade);
            trans.write(baos.toByteArray());
			trans.close();

            trans = new TSimpleFileTransport("data",
                                         ((args.length==0) ? true : false), 
                                         true);			
            byte[] buf = new byte[128];
            int iBytesRead = trans.read(buf, 0, buf.length);
            ByteArrayInputStream bais = new ByteArrayInputStream(buf);
            ObjectInputStream ois = new ObjectInputStream(bais);
            trade = (Trade) ois.readObject();
            System.out.println("Trade(" + iBytesRead + "): " + trade.symbol + " " + 
                               trade.size + " @ " + trade.price);
        } catch (TTransportException tte) {				
            System.out.println("TTransportException(" + tte.getType() + 
                               "): " + tte);
        } catch (TException te) {						
            System.out.println("TException: " + te);
        } catch (Exception e) {						
            System.out.println("Exception: " + e);
        } catch (Throwable t) {						
            System.out.println("Throwable: " + t);			
        }
    }
}

