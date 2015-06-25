import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import org.apache.thrift.TException;

public class SocialLookupHandler implements SocialLookup.Iface {

    private static class Site {

        public Site(String name, int visits) {
            this.name = name;
            this.visits = visits;
        }
        public String name;
        public int visits;
    };
    private static final Map<Integer, Site> siteRank;

    static {
        HashMap<Integer, Site> m = new HashMap<>();
        m.put(1, new Site("Facebook", 750000000));
        m.put(2, new Site("Twitter", 250000000));
        m.put(3, new Site("LinkedIn", 110000000));
        m.put(4, new Site("Pinterest", 85500000));
        m.put(5, new Site("MySpace", 70500000));
        m.put(6, new Site("Google Plus+", 65000000));
        m.put(7, new Site("DeviantArt", 25500000));
        m.put(8, new Site("LiveJournal", 20500000));
        m.put(9, new Site("Tagged", 19500000));
        m.put(10, new Site("Orkut", 17500000));
        siteRank = Collections.unmodifiableMap(m);
    }

    @Override
    public String GetSiteByRank(int rank) throws TException {
        Site s = siteRank.get(rank);
        return (null == s) ? "" : s.name;
    }

    @Override
    public int GetSiteRankByName(String name) throws TException {
        for (Map.Entry<Integer, Site> entry : siteRank.entrySet()) {
            if (name.equalsIgnoreCase(entry.getValue().name)) {
                return entry.getKey();
            }
        }
        return 0;
    }
}
