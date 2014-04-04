
import org.apache.thrift.TProcessor;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TThreadPoolServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;

public class ThreadedServer {

  public static void main(String[] args) throws TTransportException {
    TServerSocket svrTrans = new TServerSocket(8585);
    TProcessor processor = new Message.Processor<>(new MessageHandler());
    TServer server = new TThreadPoolServer(new TThreadPoolServer.Args(svrTrans).processor(processor));
    server.serve();
  }
}
