import org.thriftbook.TradeHistory;
import org.thriftbook.TradeHistoryService;

public class SoapClient {
    public static void main(String[] args) {
        TradeHistoryService svc = new TradeHistoryService();
        TradeHistory th = svc.getTradeHistoryPort();
	
        for (int i = 0; i < 1000000; i++) {
            th.getLastSale("AAPL");
        }
    }
}
