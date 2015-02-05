#!/usr/bin/env ruby

require 'thrift'
$:.push('gen-rb')
require 'hello_svc'

class HelloHandler
  def getMessage(name)
    return 'Hello ' + name
  end
end

port = 9095
handler = HelloHandler.new()
processor = HelloSvc::Processor.new(handler)
trans_svr_ep = Thrift::ServerSocket.new(port)
trans_buf_fac = Thrift::BufferedTransportFactory.new()
proto_fac = Thrift::BinaryProtocolFactory.new()
server = Thrift::SimpleServer.new(processor, trans_svr_ep, trans_buf_fac, proto_fac)

puts "Starting server on port #{port}..."
server.serve()

