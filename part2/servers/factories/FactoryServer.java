
import org.apache.thrift.TProcessor;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TThreadPoolServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.transport.TFramedTransport;

public class FactoryServer {

  public static void main(String[] args) throws TTransportException {
    TServerSocket svrTrans = new TServerSocket(8585);
    TProcessor processor = new Message.Processor<>(new MessageHandler());
    
    TServer server = new TThreadPoolServer(
            new TThreadPoolServer.Args(svrTrans)
              .processor(processor)
              .protocolFactory(new TJSONProtocol.Factory())
              .inputTransportFactory(new TFramedTransport.Factory())
              .outputTransportFactory(new TWritelogTransportFactory(100)));
    server.serve();
  }
}
