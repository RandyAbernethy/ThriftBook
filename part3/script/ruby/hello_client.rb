#!/usr/bin/env ruby

require 'thrift'
$:.push('gen-rb')
require 'hello_svc'

begin
  transport = Thrift::BufferedTransport.new(Thrift::Socket.new('localhost', 9095))
  protocol = Thrift::BinaryProtocol.new(transport)
  client = HelloSvc::Client.new(protocol)

  transport.open()

  res = client.getMessage('world')
  puts 'Message from server: ' + res
  transport.close()

rescue Thrift::Exception => tx
  print 'Thrift::Exception: ', tx.message, "\n"
end

