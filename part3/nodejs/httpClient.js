var thrift = require('thrift');
var helloSvc = require('./gen-nodejs/helloSvc.js');

var options = {
   transport: thrift.TBufferedTransport,
   protocol: thrift.TJSONProtocol,
   path: "/hello",
   headers: {"Connection": "close"},
   https: false
};

var connection = thrift.createHttpConnection("localhost", 9090, options);
var client = thrift.createHttpClient(helloSvc, connection);

connection.on("error", function(err) {
   console.log("Error: " + err);
});

client.getMessage("Thurston Howell", function(error, result) {
   console.log("Msg from server: " + result);
});


