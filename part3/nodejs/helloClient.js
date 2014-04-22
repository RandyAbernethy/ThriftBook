var thrift = require('thrift');
var helloSvc = require('./gen-nodejs/helloSvc.js');

var connection = thrift.createConnection('localhost', 8585, {
   transport: thrift.TBufferedTransport,
   protocol: thrift.TBinaryProtocol
}).on('error', function(error) {
   console.log(error);
}).on("connect", function() {
   var client = thrift.createClient(helloSvc, connection);
   client.getMessage("Thurston Howell", function(error, result) {
      console.log("Msg from server: " + result);
      connection.end();
  });
});

