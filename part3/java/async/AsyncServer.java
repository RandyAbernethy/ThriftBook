import java.io.IOException;
import java.util.concurrent.atomic.AtomicInteger;

import org.apache.thrift.TProcessor;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TThreadedSelectorServer;
import org.apache.thrift.transport.TNonblockingServerSocket;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.async.AsyncMethodCallback;


public class AsyncServer {

    public static class TradeHistoryHandler implements TradeReporting.TradeHistory.Iface {
        private AtomicInteger seq = new AtomicInteger(0);

        public TradeReporting.TradeReport get_last_sale(String Symbol) 
                throws org.apache.thrift.TException {
            int i = seq.incrementAndGet();
            if (Symbol.equals("GE")) {
                try { Thread.sleep(10000); } catch (InterruptedException ie) {;}
                return new TradeReporting.TradeReport(Symbol, 50.25, 1500, i);
            } else {
                return new TradeReporting.TradeReport(Symbol, 76.50, 500, i);
            }
        }
    }

    public static class AsyncTradeHistoryHandler 
            implements TradeReporting.TradeHistory.AsyncIface {
        TradeHistoryHandler handler = new TradeHistoryHandler();

        @Override
        public void get_last_sale(String Symbol, AsyncMethodCallback resultHandler)
                throws org.apache.thrift.TException {
            resultHandler.onComplete(handler.get_last_sale(Symbol));
        }
    }

    public static void main(String[] args)
            throws TTransportException, IOException, InterruptedException {

        TProcessor proc = 
            new TradeReporting.TradeHistory.AsyncProcessor(new AsyncTradeHistoryHandler());
        TNonblockingServerSocket svrTrans = new TNonblockingServerSocket(9090);
        TServer server = 
            new TThreadedSelectorServer(new TThreadedSelectorServer.Args(svrTrans)
                .processor(proc)
                .protocolFactory(new TBinaryProtocol.Factory())
                .workerThreads(6)
                .selectorThreads(3));
        System.out.println("[Server] listening of port 9090");
        server.serve();
    }
}
