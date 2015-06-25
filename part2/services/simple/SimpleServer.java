import org.apache.thrift.TProcessor;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;

public class SimpleServer {
    public static void main(String[] args) throws TTransportException {
        TServerSocket trans_svr = new TServerSocket(9090);
        TProcessor proc = new SocialLookup.Processor<>(new SocialLookupHandler());
        TServer server = new TSimpleServer(new TSimpleServer.Args(trans_svr).processor(proc));
        server.serve();
    }
}
