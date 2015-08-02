import com.rabbitmq.client.ConnectionFactory;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.QueueingConsumer;

import org.apache.thrift.TException;
import org.apache.thrift.transport.TTransportException;
import org.apache.thrift.transport.TMemoryBuffer;
import org.apache.thrift.protocol.TCompactProtocol;

public class TradeReader {
    private final static String QUEUE_NAME = "trade_reports";

    public static void main(String[] argv)
        throws java.io.IOException,
               java.lang.InterruptedException,
               java.util.concurrent.TimeoutException,
               TException,
               TTransportException {

        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost("localhost");
        Connection connection = factory.newConnection();
        Channel channel = connection.createChannel();
        channel.queueDeclare(QUEUE_NAME, false, false, false, null);
        QueueingConsumer consumer = new QueueingConsumer(channel);
        channel.basicConsume(QUEUE_NAME, true, consumer);

        System.out.println("Waiting for trade reports...");
        while (true) {
            QueueingConsumer.Delivery delivery = consumer.nextDelivery();
            byte[] data = delivery.getBody();
            TMemoryBuffer trans = new TMemoryBuffer(data.length);
            trans.write(data, 0, data.length);
            TCompactProtocol proto = new TCompactProtocol(trans);
            TradeReport tr = new TradeReport();
            tr.read(proto);
            System.out.println("[" + tr.seq_num + "] " + tr.symbol + 
                               " @ " + tr.price + " x " + tr.size);
        }
    }
}
