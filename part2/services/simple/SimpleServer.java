
import org.apache.thrift.TProcessor;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;

public class SimpleServer {
  public static void main(String[] args) throws TTransportException {
    TServerSocket svrTrans = new TServerSocket(8585);
    TProcessor processor = new SocialLookup.Processor<>(new SocialLookupHandler());
    TServer server = new TSimpleServer(new TSimpleServer.Args(svrTrans).processor(processor));
    server.serve();
  }
}
