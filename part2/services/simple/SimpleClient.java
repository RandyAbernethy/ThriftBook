
import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;

public class SimpleClient {
  public static void main(String[] args) throws TException {
    TTransport trans = new TSocket("localhost", 8585);
    trans.open();
    TProtocol proto = new TBinaryProtocol(trans);
    SocialLookup.Iface socialLookup = new SocialLookup.Client(proto);
    
    System.out.println("Number 1 site: " + socialLookup.GetSiteByRank(1));
    System.out.println("Twitter rank : " + socialLookup.GetSiteRankByName("Twitter"));    
  }
}
