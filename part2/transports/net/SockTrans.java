// Apache Thrift Network Transport in Java

import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TSimpleFileTransport;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;

public class SockTrans {

    public static void main(String[] args) throws TTransportException {
        //Display web page
        TTransport trans = new TSocket("thrift.apache.org", 80);
        final String msg = "GET / \n";
        trans.open();
        trans.write(msg.getBytes());
        trans.flush();							
        read_trans(trans);
        trans.close();
        //Display file
        trans = new TSimpleFileTransport("SockTrans.java");
        trans.open();
        read_trans(trans);
        trans.close();
    }

    public static void read_trans(TTransport trans) {
        final int buf_size = 1024*8;
        byte[] buf = new byte[buf_size];

        while (true) {
            try {							
                int bytes_read = trans.read(buf, 0, buf_size);
                if (bytes_read <= 0 || buf_size < bytes_read) {
                   break;
                }
                System.out.print(new String(buf, 0, bytes_read, "UTF-8"));
            } catch (Throwable t) {
                break;
            }
        }
    }
}

