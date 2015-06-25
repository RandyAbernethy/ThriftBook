import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;

public class SimpleClient {
    public static void main(String[] args) throws TException {
        TTransport trans = new TSocket("localhost", 9090);
        TProtocol proto = new TBinaryProtocol(trans);
        SocialLookup.Iface client = new SocialLookup.Client(proto);
    
        trans.open();
        System.out.println("Number 1 site: " + client.GetSiteByRank(1));
        System.out.println("Twitter rank : " + client.GetSiteRankByName("Twitter"));
        trans.close();
    }
}
