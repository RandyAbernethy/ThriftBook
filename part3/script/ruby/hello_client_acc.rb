#!/usr/bin/env ruby

require 'thrift'
$:.push('gen-rb')
require 'hello_svc'

begin
  trans_ep = Thrift::Socket.new('localhost', 9095)
  trans_buf = Thrift::BufferedTransport.new(trans_ep)
  proto = Thrift::BinaryProtocolAccelerated.new(trans_buf)
  client = HelloSvc::Client.new(proto)

  trans_ep.open()

  start = Time.now
  100000.times {res = client.getMessage('world')}
  stop = Time.now

  puts 'time: ' + (stop - start).to_s
  trans_ep.close()
rescue Thrift::Exception => tx
  print 'Thrift::Exception: ', tx.message, "\n"
end

