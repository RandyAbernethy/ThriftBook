
import org.apache.thrift.TException;


public class StandAlone {

  public static void main(String[] args) throws TException {
    SocialLookup.Iface socialLookup = new SocialLookupHandler();
    System.out.println("Number 1 site: " + socialLookup.GetSiteByRank(1));
    System.out.println("Twitter rank : " + socialLookup.GetSiteRankByName("Twitter"));    
  }
}
