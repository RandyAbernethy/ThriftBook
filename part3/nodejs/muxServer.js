var thrift = require('thrift');
var helloSvc = require('./gen-nodejs/helloSvc.js');
var byeSvc = require('./gen-nodejs/byeSvc.js');

var helloHandler = {
  getMessage: function (name, result) {
    console.log("Received: " + name);
    result(null, "Hello " + name);
  }
};

var byeHandler = {
  counter: 0,
  bye: function (result) {
    console.log("Bye called: " + (++this.counter));
    result(null, this.counter);
  }
};

var processor = new thrift.MultiplexedProcessor();
processor.registerProcessor("helloSvc", new helloSvc.Processor(helloHandler));
processor.registerProcessor("byeSvc", new byeSvc.Processor(byeHandler));

var serverOptions = {
  protocol: thrift.TBinaryProtocol,
  transport: thrift.TBufferedTransport
}
var port = 8585;

thrift.createMultiplexServer(processor, serverOptions)
  .on('error', function(error) { console.log(error); })
  .listen(port);
console.log("Thrift Mux Server running on port: " + port);

