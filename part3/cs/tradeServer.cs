using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Threading;
using Thrift.Transport;
using Thrift.Protocol;
using Thrift.Server;

namespace tradeServer {
    /// <summary>
    /// Simulate trade events
    /// </summary>
    public static class TradeEventGenerator {
        //Attributes
        private static int nextTradeId = 0;
        private static EventWaitHandle tradeEvent = new EventWaitHandle(false, EventResetMode.ManualReset);
        private static ConcurrentQueue<ConcurrentQueue<PNWF.Trade>> clients = new ConcurrentQueue<ConcurrentQueue<PNWF.Trade>>();

        //Methods
        public static void Subscribe(ConcurrentQueue<PNWF.Trade> trades) { clients.Enqueue(trades); }
        public static void WaitForTrades() { tradeEvent.WaitOne(); }
        public static void ThreadProc() {
            int[] delay = { 7000, 3000, 4000, 5000 };
            int delayIndex = 0;
            while (true) {
                Thread.Sleep(delay[++delayIndex % delay.Length]);
                List<PNWF.Trade> trades = GetMockTrades();
                foreach (ConcurrentQueue<PNWF.Trade> client in clients) {
                    foreach (PNWF.Trade trade in trades) {
                        client.Enqueue(trade);
                    }
                }
                tradeEvent.Set();
                tradeEvent.Reset();
            }
        }

        //Internal operations
        private static List<PNWF.Trade> GetMockTrades() {
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
            if (nextTradeId % 3 == 0) {
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

    public class TradeStreamHandler : PNWF.TradeStream.Iface {
        //Attributes
        private ThreadLocal<ConcurrentQueue<PNWF.Trade>> trades =
            new ThreadLocal<ConcurrentQueue<PNWF.Trade>>(() => { 
                ConcurrentQueue<PNWF.Trade> trades = new ConcurrentQueue<PNWF.Trade>();
                TradeEventGenerator.Subscribe(trades);
                return trades;
            });
        //Methods
        public List<PNWF.Trade> GetNextTrade(string fish_filter) {
            TradeEventGenerator.WaitForTrades();
            List<PNWF.Trade> returnTrades = new List<PNWF.Trade>();
            PNWF.Trade trade;
            while (trades.Value.TryDequeue(out trade)) {
                returnTrades.Add(trade);
            }
            return returnTrades;
        }
    }

    class Program {
        static void Main(string[] args) {
            (new Thread(TradeEventGenerator.ThreadProc)).Start();
            TradeStreamHandler handler = new TradeStreamHandler();
            PNWF.TradeStream.Processor proc = new PNWF.TradeStream.Processor(handler);
            TServerTransport trans = new TNamedPipeServerTransport("TradeStream");
            TTransportFactory transFac = new TTransportFactory();
            TProtocolFactory protoFac = new TCompactProtocol.Factory();
            TServer server = new TThreadedServer(proc, trans, transFac, protoFac);
            server.Serve();
        }
    }
}

