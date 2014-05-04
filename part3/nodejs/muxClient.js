var thrift = require('thrift');
var helloSvc = require('./gen-nodejs/helloSvc.js');
var byeSvc = require('./gen-nodejs/byeSvc.js');

var connection = thrift.createConnection('localhost', 8585, {
   transport: thrift.TBufferedTransport,
   protocol: thrift.TBinaryProtocol
}).on('error', function(error) {
   console.log(error);
}).on("connect", function() {
   var mp = new thrift.Multiplexer();
   var helloClient = mp.createClient("helloSvc", helloSvc, connection);
   var byeClient = mp.createClient("byeSvc", byeSvc, connection);

   helloClient.getMessage("Thurston Howell", function(error, result) {
      console.log("Hello msg from server: " + result);
   });
   byeClient.bye(function(error, result) {
      console.log("Bye msg from server: " + result);
      connection.end();
   });
});

