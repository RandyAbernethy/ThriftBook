import java.io.IOException;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.server.TThreadPoolServer;

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
        TThreadPoolServer server = 
            new TThreadPoolServer(new TThreadPoolServer.Args(trans_svr)
                    .protocolFactory(new TJSONProtocol.Factory())
                    .processor(proc));
        System.out.println("[Server] listening of port 9090");
        server.serve();
    }
}
