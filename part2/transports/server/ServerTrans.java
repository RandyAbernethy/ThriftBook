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

        TServerTransport acceptor = new TServerSocket(8585);
        acceptor.listen();
        System.out.println("[Server] listening on port 8585");

        while (true) {
            TTransport trans = acceptor.accept();
            System.out.println("[Server] handling request");
            trans.read(buf, 0, buf_size);
            if (stop_cmd.regionMatches(0, new String(buf, 0, buf.length,"UTF-8"), 0, 4)) {
               break;
            }
            trans.write(msg.getBytes());
            trans.flush();
            trans.close();
        }
        System.out.println("[Server] exiting");
        acceptor.close();
    }
}

