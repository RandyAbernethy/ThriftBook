import java.io.IOException;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TNonblockingSocket;
import org.apache.thrift.TException;
import org.apache.thrift.async.TAsyncMethodCall;
import org.apache.thrift.async.TAsyncClientManager;
import org.apache.thrift.async.AsyncMethodCallback;
import TradeReporting.TradeHistory.AsyncClient.get_last_sale_call;

public class AsyncClient {

    //Class template supporting async wait and timeout
    private static abstract class WaitableCallback<T extends TAsyncMethodCall> 
            implements AsyncMethodCallback<T> {

        private CountDownLatch latch = new CountDownLatch(1);

        //Synchronization Interface
        public void reset() { latch = new CountDownLatch(1); }
        public void complete() { latch.countDown(); }
        public boolean wait(int i) {
            boolean b = false;
            try { b = latch.await(i, TimeUnit.MILLISECONDS); }
            catch(Exception e) { System.out.println("[Client] await error"); }
            return b;
        }

        //AsyncMethodCallback<T> interface
        @Override
        public void onError(Exception ex) {
            if (ex instanceof TimeoutException) {
                System.out.println("[Client] Async call timed out");
            } else {
                System.out.println("[Client] Async call error");
            }
            complete();
        }
    }

    //Application entry point
    public static void main(String[] args) 
            throws IOException, InterruptedException, TException {
        //Async client and I/O stack setup
        TNonblockingSocket trans_ep = new TNonblockingSocket("localhost", 9090);
        TAsyncClientManager client_man = new TAsyncClientManager();
        TradeReporting.TradeHistory.AsyncClient client = 
            new TradeReporting.TradeHistory.AsyncClient(new TBinaryProtocol.Factory(),
                                                        client_man, trans_ep);

        //get_last_sale() async callback handler
        WaitableCallback<get_last_sale_call> wc = 
                new WaitableCallback<get_last_sale_call>() {

            @Override
            public void onComplete(get_last_sale_call cob) {
                try {
                    TradeReporting.TradeReport tr = cob.getResult();
                    System.out.println("[Client] received [" + tr.seq_num + "] " + 
                                       tr.symbol + " : " + tr.size + " @ " + tr.price);
                } catch (TException e) {
                    ;
                } finally {
                    complete();
                }
            }
        };

        //Make an async call
        wc.reset();
        client.get_last_sale("IBM", wc);
        System.out.println("[Client] get_last_sale() executing asynch...");
        wc.wait(500);
        wc.reset();
        client.get_last_sale("F", wc);
        wc.wait(25000);

        //Make an async call which will time out
        client.setTimeout(1000);
        wc.reset();
        client.get_last_sale("GE", wc);
        wc.wait(5000);

        //Shutdown async client manager and close network socket
        client_man.stop();
        trans_ep.close();
    }
}

