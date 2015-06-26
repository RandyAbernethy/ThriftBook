
import org.apache.thrift.TException;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.protocol.TJSONProtocol;
import org.apache.thrift.protocol.TMultiplexedProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.transport.TTransport;

public class MultiServiceClient {
    public static void main(String[] args) throws TException {
        TTransport trans = new TFramedTransport(new TSocket("localhost", 9090));
        TProtocol proto = new TJSONProtocol(trans);
    
        TMultiplexedProtocol proto_msg = new TMultiplexedProtocol(proto, "Message");
        Message.Client client_msg = new Message.Client(proto_msg);
        TMultiplexedProtocol proto_time = new TMultiplexedProtocol(proto, "ServerTime");
        ServerTime.Client client_time = new ServerTime.Client(proto_time);
    
        trans.open();
        String line;
        do {
            System.out.println("Message from server: " + client_msg.motd());
            System.out.println("Time at server: " + client_time.time_at_server((short)-1));
            System.out.println("Enter to continue, 'q' to quit: ");
            line = System.console().readLine();
        } while (0 != line.compareToIgnoreCase("q"));   
    }
}
