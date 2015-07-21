import java.io.IOException;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import org.apache.thrift.TProcessor;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TThreadedSelectorServer;
import org.apache.thrift.transport.TNonblockingServerSocket;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.async.AsyncMethodCallback;


public class AsyncServer {

    private static AtomicInteger seq = new AtomicInteger(0);

    private static class FloorQuoteReq {
        public String symbol;
        public AsyncMethodCallback callback; 

        public FloorQuoteReq(String s, AsyncMethodCallback amc) {
            symbol = s;
            callback = amc; 
        }
    }

    private static class FloorBroker implements Runnable {

        private BlockingQueue<FloorQuoteReq> manualQuoteQ;

        public FloorBroker() { 
            manualQuoteQ = new LinkedBlockingQueue<FloorQuoteReq>(); 
        }

        public BlockingQueue<FloorQuoteReq> getQ() { return manualQuoteQ; }

        @Override
        public void run() {
            try { 
                while (true) { 
                    FloorQuoteReq fqr = manualQuoteQ.take(); 
                    Thread.sleep(10000);
                    fqr.callback.onComplete(
                        new TradeReporting.TradeReport(fqr.symbol, 50.25, 1500,
                                                       seq.incrementAndGet()));
                }
            } catch (InterruptedException ex) { 
                System.out.println("[Server] Floor broker thread exiting"); 
            }
        }
    }

    public static class TradeHistoryHandler 
            implements TradeReporting.TradeHistory.Iface {

        @Override
        public TradeReporting.TradeReport get_last_sale(String symbol) {
            return new TradeReporting.TradeReport(symbol, 76.50, 500, 
                                                  seq.incrementAndGet());
        }
    }

    private static class AsyncTradeHistoryHandler 
            implements TradeReporting.TradeHistory.AsyncIface {

        private TradeHistoryHandler electronic;
        private BlockingQueue<FloorQuoteReq> manual;

        public AsyncTradeHistoryHandler(BlockingQueue<FloorQuoteReq> q) {
            manual = q;
            electronic = new TradeHistoryHandler();
        }

        @Override
        public void get_last_sale(String symbol, AsyncMethodCallback callback)
                throws org.apache.thrift.TException {
            if (symbol.length() < 3) {
                manual.add(new FloorQuoteReq(symbol, callback));
            } else {
                callback.onComplete(electronic.get_last_sale(symbol));
            }
        }
    }

    public static void main(String[] args)
            throws TTransportException, IOException, InterruptedException {

        FloorBroker floor = new FloorBroker();
        (new Thread(floor)).start();

        TProcessor proc = new TradeReporting.TradeHistory.AsyncProcessor(
            new AsyncTradeHistoryHandler(floor.getQ()));
        TNonblockingServerSocket trans_svr = new TNonblockingServerSocket(9090);
        TServer server = 
            new TThreadedSelectorServer(new TThreadedSelectorServer.Args(trans_svr)
                .processor(proc)
                .protocolFactory(new TBinaryProtocol.Factory())
                .workerThreads(6)
                .selectorThreads(3));
        System.out.println("[Server] listening of port 9090");
        server.serve();
    }
}
