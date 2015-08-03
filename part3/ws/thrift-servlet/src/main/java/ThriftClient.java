import java.io.IOException;
import org.apache.thrift.TException;
import org.apache.thrift.transport.THttpClient;
import org.apache.thrift.protocol.TJSONProtocol;

public class ThriftClient {
    public static void main(String[] args) 
            throws IOException, TException {
        THttpClient trans = new THttpClient("http://localhost:8080/thrift-servlet");
        TJSONProtocol proto = new TJSONProtocol(trans);
        TradeHistory.Client client = new TradeHistory.Client(proto);

        for (int i = 0; i < 1000000; i++) {
            trans.open();
            TradeReport tr = client.get_last_sale("AAPL");
            trans.close();
        }
    }
}

