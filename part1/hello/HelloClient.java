// Apache Thrift Hello World Java Client

import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.TException;

public class HelloClient {

    public static void main(String[] args) throws TException {
        TSocket socket = new TSocket("localhost", 8585);
        socket.open();
        TBinaryProtocol protocol = new TBinaryProtocol(socket);
        
        HelloSvc.Client client = new HelloSvc.Client(protocol);
        String str = client.hello_func();
        System.out.println("[Client] received: " + str);
    }
}

