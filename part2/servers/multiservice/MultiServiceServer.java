import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import org.apache.thrift.TMultiplexedProcessor;
import org.apache.thrift.server.TServer;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.server.TThreadedSelectorServer;
import org.apache.thrift.transport.TNonblockingServerSocket;

public class MultiServiceServer {

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

    public static void main(String[] args) throws TTransportException, IOException, InterruptedException {
        TNonblockingServerSocket trans_svr = new TNonblockingServerSocket(9090);
        TMultiplexedProcessor proc = new TMultiplexedProcessor();
        proc.registerProcessor("Message", new Message.Processor<>(new MessageHandler()));
        proc.registerProcessor("ServerTime", new ServerTime.Processor<>(new ServerTimeHandler()));

        TServer server = new TThreadedSelectorServer(
                new TThreadedSelectorServer.Args(trans_svr)
                .processor(proc)
                .protocolFactory(new TJSONProtocol.Factory())
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
