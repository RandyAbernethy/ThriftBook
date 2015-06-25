// Apache Thrift Server Transport in Java

import java.io.UnsupportedEncodingException;
import org.apache.thrift.transport.TServerSocket;
import org.apache.thrift.transport.TServerTransport;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;

public class ServerTrans {

    public static void main(String[] args) 
           throws TTransportException, UnsupportedEncodingException {
        final String msg = "Hello Thrift!\n";
        final String stop_cmd = "STOP";
        final int buf_size = 1024*8;
        byte[] buf = new byte[buf_size];
        final int port = 9090;

        TServerTransport acceptor = new TServerSocket(9090);
        acceptor.listen();
        System.out.println("[Server] listening on port: " + port);
        
        String input;
        do {
            TTransport trans = acceptor.accept();
            int len = trans.read(buf, 0, buf_size);
            input = new String(buf, 0, len,"UTF-8");
            System.out.println("[Server] handling request: " + input);
            trans.write(msg.getBytes());
            trans.flush();
            trans.close();
        } while (! stop_cmd.regionMatches(0, input, 0, 4)); 

        System.out.println("[Server] exiting");
        acceptor.close();
    }
}

