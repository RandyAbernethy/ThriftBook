
import org.apache.thrift.TException;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;

public class FactoryClient {
  public static void main(String[] args) throws TException {
    TTransport trans = new TFramedTransport(new TSocket("localhost", 8585));
    TProtocol proto = new TJSONProtocol(trans);
    Message.Iface client = new Message.Client(proto);
    trans.open();
    String line;
    do {
       System.out.println("Message from server: " + client.motd());
       System.out.println("Enter to continue, 'q' to quit: ");
       line = System.console().readLine();
    } while (0 != line.compareToIgnoreCase("q"));   
  }
}
