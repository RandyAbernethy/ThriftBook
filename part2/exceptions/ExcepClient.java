// Apache Thrift User Defined Exception Client in Java

import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.TException;

public class ExcepClient {
    public static void main(String[] args) throws TException {
        TSocket socket = new TSocket("localhost", 8585);
        socket.open();
        TBinaryProtocol protocol = new TBinaryProtocol(socket);
        TradeHistory.Client client = new TradeHistory.Client(protocol);
        try {
            double price = client.GetLastSale(args[0]);
            System.out.println("[Client] received: " + price);
        } catch (BadFish bf) {
            System.out.println("[Client] GetLastSale() call failed for fish: " + bf.fish + ", error " + bf.error_code);
        }
    }
}

