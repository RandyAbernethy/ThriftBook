var fs = require("fs");					
var thrift = require('thrift');
var helloSvc = require('./gen-nodejs/helloSvc');

var helloHandler = {
  getMessage: function(name, result) {
    var msg = "Hello " + name + "!";
    console.log(msg);
    result(null, msg);
  }
}

var helloSvcOpt = {
    transport: thrift.TBufferedTransport,
    protocol: thrift.TJSONProtocol,
    processor: helloSvc,
    handler: helloHandler
};

var serverOpt = {
    filePath: ".",
    tls: {						
      key: fs.readFileSync("key.pem"),		
      cert: fs.readFileSync("cert.pem")		
    },						
    services: {
        "/hello": helloSvcOpt
    }
}

var port = 9099;
thrift.createWebServer(serverOpt).listen(port);
console.log("Https/Thrift Server running on port: " + port);

