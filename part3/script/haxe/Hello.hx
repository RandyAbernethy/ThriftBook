import org.apache.thrift.*;
import org.apache.thrift.protocol.*;
import org.apache.thrift.transport.*;

class Hello {
    static function main() {
        try {
            var trans_ep = new TSocket("localhost", 9095);
            var trans_buf = new TBufferedTransport(trans_ep);
            var proto = new TBinaryProtocol(trans_buf);
            var client = new HelloSvcImpl(proto, proto);

            trans_ep.open();
            var msg = client.getMessage("World!");
            trans_ep.close();
            trace(msg);
        } catch(error : TException) {
            trace('Error: $error');
        }
    }
}
 
