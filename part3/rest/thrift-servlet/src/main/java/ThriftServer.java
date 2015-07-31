import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.server.TServlet;

public class ThriftServer extends TServlet {
    public static class TradeHistoryHandler implements TradeHistory.Iface {
        @Override
        public TradeReport get_last_sale(String symbol) {
            return new TradeReport(symbol, 25.50, 100, 1);
        }
    }

    public ThriftServer() {
        super(new TradeHistory.Processor(new TradeHistoryHandler()),
              new TJSONProtocol.Factory());
    }
}
