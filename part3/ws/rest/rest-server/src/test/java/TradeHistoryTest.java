import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import java.net.URI;
import org.glassfish.jersey.grizzly2.httpserver.GrizzlyHttpServerFactory;
import org.glassfish.jersey.server.ResourceConfig;
import org.glassfish.grizzly.http.server.HttpServer;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class TradeHistoryTest {
    private HttpServer server;
    private WebTarget target;

    @Before
    public void setUp() throws Exception {
        server = GrizzlyHttpServerFactory.createHttpServer(
                    URI.create(RestServer.BASE_URI), 
                    new ResourceConfig().registerClasses(RestServer.class));
        Client c = ClientBuilder.newClient();
        target = c.target(RestServer.BASE_URI);
    }

    @After
    public void tearDown() throws Exception {
        server.stop();
    }

    @Test
    public void test_get_last_sale() {
        final RestServer.TradeReport obj = 
            target.path("tradehistory/get_last_sale")
                  .queryParam("symbol", "AAPL")
                  .request(MediaType.APPLICATION_JSON_TYPE)
                  .get(RestServer.TradeReport.class);
        assertEquals("AAPL", obj.symbol);
    }
}
