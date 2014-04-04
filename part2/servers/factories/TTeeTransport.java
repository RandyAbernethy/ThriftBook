
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;

public class TTeeTransport extends TTransport {

  private TTransport left;
  private TTransport right;

  public TTeeTransport(TTransport left, TTransport right) {
    this.left = left;
    this.right = right;
  }

  @Override
  public void flush() throws TTransportException {
    left.flush();
    right.flush();
  }

  @Override
  public boolean isOpen() {
    return true;
  }

  @Override
  public void open() throws TTransportException {
    throw new TTransportException("read not supported");
  }

  @Override
  public void close() {
    left.close();
    right.close();
  }

  @Override
  public int read(byte[] bytes, int i, int i1) throws TTransportException {
    throw new TTransportException("read not supported");
  }

  @Override
  public void write(byte[] bytes, int i, int i1) throws TTransportException {
    left.write(bytes, i, i1);
    right.write(bytes, i, i1);
  }
}

