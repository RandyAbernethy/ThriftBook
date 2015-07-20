import org.apache.thrift.TProcessor;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.TException;

public class HelloServer {

    public static class MessageHandler implements helloSvc.Iface {

        @Override
        public String getMessage(String name) throws TException {
            System.out.println("[Server] received: " + name);
            return "Hello " + name;
        }
    }

    public static void main(String[] args) throws TTransportException {
        TServerSocket trans_svr = new TServerSocket(9090);
        TProcessor proc = new helloSvc.Processor<>(new MessageHandler());
        TSimpleServer server = 
            new TSimpleServer(
                new TSimpleServer.Args(trans_svr)
                    .processor(proc)
            );
        System.out.println("[Server] waiting for connections");
        server.serve();
    }
}
