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
endpointSvrTrans = Thrift::ServerSocket.new(port)
layeredTransFac = Thrift::BufferedTransportFactory.new()
protoFac = Thrift::BinaryProtocolFactory.new()
server = Thrift::SimpleServer.new(processor, endpointSvrTrans, layeredTransFac, protoFac)

puts "Starting server on port #{port}..."
server.serve()

