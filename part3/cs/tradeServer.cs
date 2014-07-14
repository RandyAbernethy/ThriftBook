using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Threading;
using Thrift.Transport;
using Thrift.Protocol;
using Thrift.Server;

namespace tradeServer
{
  /// <summary>
  /// Simulate trade events
  /// 
  /// This class requries each client connection to be hosted by a seperate 
  /// thread. A thread local event is used as a key to return a unique 
  /// trade queue for each connection.
  /// </summary>
  public static class TradeEventGenerator
  {
    //Thread Local Attribute
    public static ThreadLocal<EventWaitHandle> tradeEvent = new ThreadLocal<EventWaitHandle>(() =>
    {
      return new EventWaitHandle(false, EventResetMode.AutoReset);
    });

    //Attributes
    private static int nextTradeId = 0;
    private static ConcurrentDictionary<EventWaitHandle, ConcurrentQueue<PNWF.Trade>> clients =
      new ConcurrentDictionary<EventWaitHandle, ConcurrentQueue<PNWF.Trade>>();

    //Methods
    public static void WaitForTrades() { TradeEventGenerator.tradeEvent.Value.WaitOne(); }
    public static ConcurrentQueue<PNWF.Trade> GetTrades() { return clients[TradeEventGenerator.tradeEvent.Value]; }
    public static void Subscribe(ConcurrentQueue<PNWF.Trade> trades) { clients[TradeEventGenerator.tradeEvent.Value] = trades; }
    public static void Unsubscribe() { ConcurrentQueue<PNWF.Trade> trades; clients.TryRemove(TradeEventGenerator.tradeEvent.Value, out trades); }

    //Background trade generator thread entry point
    public static void ThreadProc()
    {
      int[] delay = { 7000, 3000, 4000, 5000 };
      int delayIndex = 0;
      while (true)
      {
        Thread.Sleep(delay[++delayIndex % delay.Length]);
        List<PNWF.Trade> trades = GetMockTrades();
        foreach (KeyValuePair<EventWaitHandle, ConcurrentQueue<PNWF.Trade>> pair in clients)
        {
          foreach (PNWF.Trade trade in trades)
          {
            pair.Value.Enqueue(trade);
          }
          pair.Key.Set();
        }
      }
    }

    //Internal operations
    private static List<PNWF.Trade> GetMockTrades()
    {
      List<PNWF.Trade> trades = new List<PNWF.Trade>();

      PNWF.Trade trade = new PNWF.Trade();
      trade.Id = ++nextTradeId;
      trade.Fish = "Halibut";
      trade.Price = 45.75;
      trade.Amount = new PNWF.FishSizeUnit();
      trade.Amount.Kilograms = 50;
      trade.Market = PNWF.Market.SanFrancisco;
      trade.Date_time = new PNWF.TimeStamp();
      DateTime now = DateTime.Now;
      trade.Date_time.Year = (short)now.Year;
      trade.Date_time.Month = (short)now.Month;
      trade.Date_time.Day = (short)now.Day;
      trade.Date_time.Hour = (short)now.Hour;
      trade.Date_time.Minute = (short)now.Minute;
      trade.Date_time.Second = (short)now.Second;
      trade.Date_time.Micros = now.Millisecond * 1000;
      trades.Add(trade);
      if (nextTradeId % 3 == 0)
      {
        PNWF.Trade trade2 = new PNWF.Trade();
        trade2.Id = ++nextTradeId;
        trade2.Fish = "Salmon";
        trade2.Price = 65.42;
        trade2.Amount = new PNWF.FishSizeUnit();
        trade2.Amount.Pounds = 31;
        trade2.Market = PNWF.Market.Anchorage;
        trade2.Date_time = trade.Date_time;
        trades.Add(trade2);
      }
      return trades;
    }
  }

  /// <summary>
  /// Long polling Trade Stream RPC Service implementation
  /// </summary>
  public class TradeStreamHandler : PNWF.TradeStream.Iface
  {
    //Methods
    public List<PNWF.Trade> GetNextTrade(string fish_filter)
    {
      //Wait for trades
      TradeEventGenerator.WaitForTrades();

      //Recover thread specific trade queue
      ConcurrentQueue<PNWF.Trade> trades = TradeEventGenerator.GetTrades();

      //Move the trades into the return list an return it to the client
      List<PNWF.Trade> returnTrades = new List<PNWF.Trade>();
      PNWF.Trade trade;
      while (trades.TryDequeue(out trade))
      {
        if (fish_filter.Length == 0 || fish_filter.CompareTo(trade.Fish) == 0)
          returnTrades.Add(trade);
      }
      return returnTrades;
    }
  }

  /// <summary>
  /// Server Event Handler used to subscribe and unsubscribe each client 
  /// connection to the trade stream
  /// </summary>
  public class TradeServerEventHandler : TServerEventHandler
  {
    public void preServe()
    {
      Console.WriteLine("Server ready to receive connections");
    }
    public Object createContext(Thrift.Protocol.TProtocol input, Thrift.Protocol.TProtocol output)
    {
      Console.WriteLine("Client connected");
      TradeEventGenerator.Subscribe(new ConcurrentQueue<PNWF.Trade>());
      return null;
    }
    public void deleteContext(Object serverContext, Thrift.Protocol.TProtocol input, Thrift.Protocol.TProtocol output)
    {
      Console.WriteLine("Client disconnected");
      TradeEventGenerator.Unsubscribe();
    }
    public void processContext(Object serverContext, Thrift.Transport.TTransport transport)
    {
      Console.WriteLine("Waiting for next client trade request");
    }
  };

  class Program
  {
    static void Main(string[] args)
    {
      //Start the background mock trade generator thread
      (new Thread(TradeEventGenerator.ThreadProc)).Start();

      //Create the Service Handler and Processor
      TradeStreamHandler handler = new TradeStreamHandler();
      PNWF.TradeStream.Processor proc = new PNWF.TradeStream.Processor(handler);

      //Setup the I/O stack factories
      TServerTransport trans = new TNamedPipeServerTransport("TradeStream");
      TTransportFactory transFac = new TTransportFactory();
      TProtocolFactory protoFac = new TCompactProtocol.Factory();

      //Setup the server and register the event handler
      TServer server = new TThreadedServer(proc, trans, transFac, protoFac);
      server.setEventHandler(new TradeServerEventHandler());
      server.Serve();
    }
  }
}
