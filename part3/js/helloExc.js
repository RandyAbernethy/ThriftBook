var thrift = require('thrift');
var badMsg = require('./gen-nodejs/helloExc_types').badMsg;	
var helloError = require('./gen-nodejs/helloError');

var helloHandler = {
  getMessage: function(name, result) {
    if (typeof name !== "string" || name.length < 1) {		
      var e = new badMsg();						
      e.error_code = 13;						
      e.msg = "No name";						
      result(e, null);						
    } else {
      result(null, "Hello " + name + "!");
    }
  }
}

var helloErrorOpt = {
    transport: thrift.TBufferedTransport,
    protocol: thrift.TJSONProtocol,
    processor: helloError,
    handler: helloHandler
};

var serverOpt = {
    filePath: ".",
    services: { "/hello": helloErrorOpt }
}

var server = thrift.createWebServer(serverOpt);
var port = 9099;
server.listen(port);
console.log("Http/Thrift Server running on port: " + port);
console.log("Serving files from: " + __dirname);

