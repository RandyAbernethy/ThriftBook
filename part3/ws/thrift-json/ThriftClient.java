import java.io.IOException;
import org.apache.thrift.TException;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.protocol.TJSONProtocol;

public class ThriftClient {
    public static void main(String[] args) 
            throws IOException, TException {
        TSocket trans = new TSocket("localhost", 9090);
        TJSONProtocol proto = new TJSONProtocol(trans);
        TradeHistory.Client client = new TradeHistory.Client(proto);

        trans.open();
        for (int i = 0; i < 1000000; i++) {
            TradeReport tr = client.get_last_sale("APPL");
        }
        trans.close();
    }
}

