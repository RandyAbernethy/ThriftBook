using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Thrift.Protocol;
using Thrift.Transport;

namespace tradeClient
{
  class Program
  {
    static void Main(string[] args)
    {
      TTransport trans = new TNamedPipeClientTransport("TradeStream");
      trans.Open();
      TProtocol proto = new TCompactProtocol(trans);
      PNWF.TradeStream.Client client = new PNWF.TradeStream.Client(proto);
      try
      {
        for (int i = 0; i < 100; i++)
        {
          List<PNWF.Trade> trades = client.GetNextTrade("");
          foreach (PNWF.Trade trade in trades)
          {
            Console.Out.WriteLine(trade.Date_time.Hour.ToString("D2") + ":" +
                trade.Date_time.Minute.ToString("D2") + ":" + trade.Date_time.Second.ToString("D2") + " " +
                trade.Fish + "-" + trade.Market.ToString() + " " + trade.Price);
          }
        }
      }
      catch (TTransportException ex)
      {
        Console.WriteLine("Exception: " + ex.Message);
      }
    }
  }
}
