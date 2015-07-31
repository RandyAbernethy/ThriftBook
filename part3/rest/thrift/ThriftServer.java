import java.io.IOException;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.server.TSimpleServer;

public class ThriftServer {
    public static class TradeHistoryHandler implements TradeHistory.Iface {
        @Override
        public TradeReport get_last_sale(String symbol) {
            return new TradeReport(symbol, 25.50, 100, 1);
        }
    }

    public static void main(String[] args)
            throws TTransportException, IOException {
        TradeHistory.Processor proc = 
            new TradeHistory.Processor(new TradeHistoryHandler());
        TServerSocket trans_svr = 
            new TServerSocket(9090);
        TSimpleServer server = 
            new TSimpleServer(new TSimpleServer.Args(trans_svr).processor(proc));
        System.out.println("[Server] listening of port 9090");
        server.serve();
    }
}
