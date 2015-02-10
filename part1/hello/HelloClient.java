// Apache Thrift Hello World Java Client

import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.TException;

public class HelloClient {

    public static void main(String[] args) throws TException {
        TSocket trans_ep = new TSocket("localhost", 9095);
        TBinaryProtocol protocol = new TBinaryProtocol(trans_ep);
        HelloSvc.Client client = new HelloSvc.Client(protocol);

        trans_ep.open();
        String str = client.hello_func();
        System.out.println("[Client] received: " + str);
    }
}

