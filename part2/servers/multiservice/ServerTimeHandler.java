import org.apache.thrift.TException;

public class ServerTimeHandler implements ServerTime.Iface {

    @Override
    public String time_at_server(short HourOffset) throws TException {
        long theTime = System.currentTimeMillis();
        long mils = theTime % 1000;  theTime /= 1000;
        long seconds = theTime % 60;  theTime /= 60;
        long minutes = theTime % 60;  theTime /= 60;
        long hours = (theTime + HourOffset) % 24;
        return "server time: " + hours + ":" + minutes + ":" + seconds;
    }
}
