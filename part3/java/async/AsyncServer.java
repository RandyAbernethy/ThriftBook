import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.concurrent.atomic.AtomicInteger;

import org.apache.thrift.TProcessor;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TThreadedSelectorServer;
import org.apache.thrift.transport.TNonblockingServerSocket;
import org.apache.thrift.transport.TTransportException;


public class AsyncServer {
    public static class TradeHistoryHandler implements TradeReporting.TradeHistory.Iface {
        AtomicInteger seq = new AtomicInteger(0);

        public TradeReporting.TradeReport get_last_sale(String Symbol) throws org.apache.thrift.TException {
            if (Symbol.equals("GE")) {
                return new TradeReporting.TradeReport(Symbol, 50.25, 1500, seq.incrementAndGet());
            } else {
                return new TradeReporting.TradeReport(Symbol, 76.50, 500, seq.incrementAndGet());
            }
        }
    }

    public static class AsyncTradeHistoryHandler implements TradeReporting.TradeHistory.AsyncIface {
        TradeHistoryHandler handler = new TradeHistoryHandler();

        @Override
        public void get_last_sale(String Symbol, org.apache.thrift.async.AsyncMethodCallback resultHandler) throws org.apache.thrift.TException {
            resultHandler.onComplete(handler.get_last_sale(Symbol));
        }
    }

    static class RunnableServer implements Runnable {
        public RunnableServer(TServer svr) {
            this.svr = svr;
        }

        @Override
        public void run() {
            svr.serve();
        }

        private TServer svr;
    }


    public static void main(String[] args)
            throws TTransportException, IOException, InterruptedException {

        TProcessor proc = new TradeReporting.TradeHistory.AsyncProcessor(new AsyncTradeHistoryHandler());

        TNonblockingServerSocket svrTrans = new TNonblockingServerSocket(9090);
        TServer server = new TThreadedSelectorServer(new TThreadedSelectorServer.Args(svrTrans)
                .processor(proc)
                .protocolFactory(new TBinaryProtocol.Factory())
                .workerThreads(6)
                .selectorThreads(3));
        Thread server_thread = new Thread(new RunnableServer(server), "server_thread");
        server_thread.start();

        System.out.println("[Server] press enter to shutdown> ");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        br.readLine();
        System.out.println("[Server] shutting down...");
        server.stop();
        server_thread.join();
        System.out.println("[Server] down, exiting");
    }
}
