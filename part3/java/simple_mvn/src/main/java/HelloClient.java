// Apache Thrift Hello World Java Client

import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.TException;

public class HelloClient {

    public static void main(String[] args) {
        TSocket trans = new TSocket("localhost", 9090);
        TBinaryProtocol proto = new TBinaryProtocol(trans);
        helloSvc.Client client = new helloSvc.Client(proto);

        try {
            trans.open();
            String str = client.getMessage("world");
            System.out.println("[Client] received: " + str);
        } catch (TException ex) {
            System.out.println("Error: " + ex.toString());
        }
        trans.close();
    }
}
