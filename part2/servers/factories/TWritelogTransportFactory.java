
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.transport.TSimpleFileTransport;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.transport.TTransportFactory;

public class TWritelogTransportFactory extends TTransportFactory {

  private int clientID = 0;

  public TWritelogTransportFactory(int clientStartID) {
    clientID = clientStartID;
  }

  @Override
  public TTransport getTransport(TTransport trans) {
    TSimpleFileTransport log;
    try {
      log = new TSimpleFileTransport("svr_log_" + ++clientID, false, true);
      log.open();
    } catch (TTransportException ex) {
      log = null;
    }
    TFramedTransport frame = new TFramedTransport(trans);
    return new TTeeTransport(frame, log);
  }
}

