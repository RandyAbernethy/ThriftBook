var thrift = require('thrift');
var helloSvc = require('./gen-nodejs/helloSvc.js');

var helloHandler = {
  getMessage: function (name, result) {
    console.log("Received: " + name);
    result("yikes!!", null);
    //result(null, "Hello " + name);
  }
};

var serverOpt = {
  protocol: thrift.TBinaryProtocol,
  transport: thrift.TBufferedTransport
}
var port = 8585;

thrift.createServer(helloSvc, helloHandler, serverOpt)
  .on('error', function(error) { console.log(error); })
  .listen(port);
console.log("Thrift Server running on port: " + port);


