using System;
using Thrift.Transport;
using Thrift.Server;

namespace helloServer
{
    public class HelloHandler : helloSvc.Iface
    {
        public string getMessage(string name)
        {
            Console.WriteLine("Received from client: " + name);
            return "Hello " + name;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            int port = 8585;
            HelloHandler handler = new HelloHandler();
            helloSvc.Processor proc = new helloSvc.Processor(handler);
            TServerTransport trans = new TServerSocket(port, 0, true);
            TServer server = new TSimpleServer(proc, trans);
            Console.WriteLine("Server running on port " + port);
            server.Serve();
        }
    }
}
