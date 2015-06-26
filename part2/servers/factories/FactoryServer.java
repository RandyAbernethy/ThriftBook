
import org.apache.thrift.TProcessor;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TThreadPoolServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.transport.TFramedTransport;

public class FactoryServer {

  public static void main(String[] args) throws TTransportException {
    TServerSocket trans_svr = new TServerSocket(9090);
    TProcessor proc = new Message.Processor<>(new MessageHandler());
    
    TServer server = new TThreadPoolServer(
            new TThreadPoolServer.Args(trans_svr)
              .processor(proc)
              .protocolFactory(new TJSONProtocol.Factory())
              .inputTransportFactory(new TFramedTransport.Factory())
              .outputTransportFactory(new TWritelogTransportFactory(100)));
    server.serve();
  }
}
