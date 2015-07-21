// Apache Thrift Async Java Client

import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.TException;

public class AsyncClient {

    public static void main(String[] args) {
        TSocket trans_ep = new TSocket("localhost", 9090);
        TFramedTransport trans = new TFramedTransport(trans_ep);
        TBinaryProtocol proto = new TBinaryProtocol(trans);
        TradeReporting.TradeHistory.Client client = 
                new TradeReporting.TradeHistory.Client(proto);

        try {
            trans.open();
            TradeReporting.TradeReport tr = client.get_last_sale("GE");
            System.out.println("[Client] received [" + tr.seq_num + "] " + tr.symbol + " : " + tr.size + " @ " + tr.price);
        } catch (TException ex) {
            System.out.println("Error: " + ex.toString());
        }
        trans.close();
    }
}

