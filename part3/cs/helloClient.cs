using System;
using Thrift.Protocol;
using Thrift.Transport;

namespace helloClient
{
    class Program
    {
        static void Main(string[] args)
        {
            TTransport trans = new TSocket("localhost", 8585);
            trans = new TBufferedTransport(trans as TStreamTransport);
            trans.Open();
            TBinaryProtocol proto = new TBinaryProtocol(trans);
            helloSvc.Client client = new helloSvc.Client(proto);
            string result = client.getMessage("Ginger");
            Console.WriteLine("Received from server: " + result);
        }
    }
}
