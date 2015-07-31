package com.example;

import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;

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
        server = QuoteServer.startServer();
        Client c = ClientBuilder.newClient();
        target = c.target(QuoteServer.BASE_URI);
    }

    @After
    public void tearDown() throws Exception {
        server.stop();
    }

    @Test
    public void test_get_last_sale() {
        final QuoteServer.TradeReport obj = 
            target.path("tradehistory/get_last_sale")
                  .queryParam("symbol", "IBM")
                  .request(MediaType.APPLICATION_JSON_TYPE)
                  .get(QuoteServer.TradeReport.class);
        assertEquals("IBM", obj.symbol);
    }
}
