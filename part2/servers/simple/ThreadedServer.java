import org.apache.thrift.TProcessor;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TThreadPoolServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;

public class ThreadedServer {

    public static void main(String[] args) throws TTransportException {
        TServerSocket trans_svr = new TServerSocket(9090);
        TProcessor proc = new Message.Processor<>(new MessageHandler());
        TServer server = new TThreadPoolServer(new TThreadPoolServer.Args(trans_svr).processor(proc));
        server.serve();
    }
}
