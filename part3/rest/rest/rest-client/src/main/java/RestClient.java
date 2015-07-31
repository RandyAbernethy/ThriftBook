import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import java.io.IOException;

public class RestClient {
    public static final String BASE_URI = "http://localhost:8080/rest/";

    public static class TradeReport {
        public String  symbol;
        public double  price;
        public int     size;
        public int     seq_num;

        public TradeReport(){}
        public TradeReport(String symbol, double price, int size, int seq_num) {
            this.symbol = symbol;
            this.price = price;
            this.size = size;
            this.seq_num = seq_num;
        }
    } 

    public static void main(String[] args) throws IOException {
        Client c = ClientBuilder.newClient();
        WebTarget target = c.target(BASE_URI);

        for (int i = 0; i < 1000000; i++) {
            final TradeReport tr = 
                target.path("tradehistory/get_last_sale")
                      .queryParam("symbol", "AAPL")
                      .request(MediaType.APPLICATION_JSON_TYPE)
                      .get(TradeReport.class);
        }
    }
}

