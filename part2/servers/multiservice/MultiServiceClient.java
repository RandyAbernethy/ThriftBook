
import org.apache.thrift.TException;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.protocol.TMultiplexedProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.transport.TTransport;

public class MultiServiceClient {
  public static void main(String[] args) throws TException {
    TTransport trans = new TFramedTransport(new TSocket("localhost", 8585));
    TProtocol proto = new TJSONProtocol(trans);
    
    TMultiplexedProtocol msgMProto = new TMultiplexedProtocol(proto, "Message");
    Message.Client msgClient = new Message.Client(msgMProto);
    TMultiplexedProtocol timeMProto = new TMultiplexedProtocol(proto, "ServerTime");
    ServerTime.Client timeClient = new ServerTime.Client(timeMProto);
    
    trans.open();
    String line;
    do {
       System.out.println("Message from server: " + msgClient.motd());
       System.out.println("Time at server: " + timeClient.time_at_server((short)-1));
       System.out.println("Enter to continue, 'q' to quit: ");
       line = System.console().readLine();
    } while (0 != line.compareToIgnoreCase("q"));   
  }
}
