// Apache Thrift Frame Layer Network Transport Server in Java

import java.io.UnsupportedEncodingException;
import java.net.SocketException;
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TServerTransport;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;

public class ServerFrame {

    public static void main(String[] args) 
            throws TTransportException, UnsupportedEncodingException, SocketException {
        final String msg = "Hello Thrift!\n";
        final String stop_cmd = "STOP";
        final int buf_size = 1024*8;
        byte[] buf = new byte[buf_size];
        final int port = 9090;

        TServerTransport acceptor = new TServerSocket(port);
        acceptor.listen();
        System.out.println("[Server] listening on port " + port);

        while (true) {
            TTransport trans_ep = acceptor.accept();
			TTransport trans = new TFramedTransport(trans_ep);
            int len = trans.read(buf, 0, buf_size);
            String input = new String(buf, 0, len, "UTF-8");
            System.out.println("[Server] handling request: " + input);
            trans.write(msg.getBytes());
            trans.flush();
            trans.close();
            if (stop_cmd.regionMatches(0, input, 0, 4)) {
               break;
            }
        }
        System.out.println("[Server] exiting");
        acceptor.close();
    }
}
