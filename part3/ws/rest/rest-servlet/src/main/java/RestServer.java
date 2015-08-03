import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;

@Path("tradehistory")
public class RestServer {
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

    @GET
    @Path("/get_last_sale")
    @Produces(MediaType.APPLICATION_JSON)
    public TradeReport get_last_sale(@QueryParam("symbol") String symbol) {
        return new TradeReport(symbol, 25.50, 100, 1);
    }
}
