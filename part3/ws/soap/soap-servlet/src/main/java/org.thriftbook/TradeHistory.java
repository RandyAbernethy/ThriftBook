package org.thriftbook;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
 
@WebService
@SOAPBinding(style = SOAPBinding.Style.RPC)
public class TradeHistory {
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
 
    @WebMethod(operationName = "get_last_sale")
    public TradeReport get_last_sale(@WebParam(name="symbol") String symbol){
        return new TradeReport(symbol, 25.50, 100, 1);
    }
}
