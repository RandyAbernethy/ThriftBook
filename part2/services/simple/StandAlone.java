import org.apache.thrift.TException;

public class StandAlone {

    public static void main(String[] args) throws TException {
        SocialLookup.Iface handler = new SocialLookupHandler();
        System.out.println("Number 1 site: " + handler.GetSiteByRank(1));
        System.out.println("Twitter rank : " + handler.GetSiteRankByName("Twitter"));
    }
}
