#!/usr/bin/env ruby

require 'thrift'
$:.push('gen-rb')
require 'hello_svc'

class HelloHandler
  def getMessage(name)
    return "Hello " + name
  end
end

handler = HelloHandler.new()
processor = HelloSvc::Processor.new(handler)
transport = Thrift::ServerSocket.new(9095)
transportFactory = Thrift::BufferedTransportFactory.new()
server = Thrift::SimpleServer.new(processor, transport, transportFactory)

puts "Starting the server..."
server.serve()
puts "done."

