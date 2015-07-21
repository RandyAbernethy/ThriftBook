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

    public static void main(String[] args) 
            throws IOException, InterruptedException, TException {
        TAsyncClientManager client_man = new TAsyncClientManager();
        TNonblockingSocket trans_ep = new TNonblockingSocket("localhost", 9090);
        TradeReporting.TradeHistory.AsyncClient client = 
                new TradeReporting.TradeHistory.AsyncClient(new TBinaryProtocol.Factory(), 
                                                            client_man, trans_ep);

        final CountDownLatch latch = new CountDownLatch(1);
        client.get_last_sale("IBM", new AsyncMethodCallback<TradeReporting.TradeHistory.AsyncClient.get_last_sale_call>() {
            @Override
            public void onError(Exception ex) {
                if (ex instanceof TimeoutException) {
                    System.out.println("Async call timed out");
                } else {
                    System.out.println("Async call error");
                }
                latch.countDown();
            }

            @Override
            public void onComplete(TradeReporting.TradeHistory.AsyncClient.get_last_sale_call cob) {
                try {
                    TradeReporting.TradeReport tr = cob.getResult();
                    System.out.println("[Client] received [" + tr.seq_num + "] " + tr.symbol + " : " + tr.size + " @ " + tr.price);
                } catch (TException e) {
                    ;
                } finally {
                    latch.countDown();
                }
            }
        });
        boolean res = latch.await(2, TimeUnit.SECONDS);

        client.setTimeout(1000);
        final CountDownLatch latch2 = new CountDownLatch(1);
        client.get_last_sale("GE", new AsyncMethodCallback<TradeReporting.TradeHistory.AsyncClient.get_last_sale_call>() {
            @Override
            public void onError(Exception ex) {
                if (ex instanceof TimeoutException) {
                    System.out.println("Async call timed out");
                } else {
                    System.out.println("Async call error");
                }
                latch2.countDown();
            }

            @Override
            public void onComplete(TradeReporting.TradeHistory.AsyncClient.get_last_sale_call cob) {
                try {
                    TradeReporting.TradeReport tr = cob.getResult();
                    System.out.println("[Client] received [" + tr.seq_num + "] " + tr.symbol + " : " + tr.size + " @ " + tr.price);
                } catch (TException e) {
                    ;
                } finally {
                    latch2.countDown();
                }
            }
        });
        boolean calledBack = latch2.await(2, TimeUnit.SECONDS);
        client_man.stop();
        trans_ep.close();
    }
}

