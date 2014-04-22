var thrift = require('thrift');
var helloSvc = require('./gen-nodejs/helloSvc.js');
var Q = require('q');

var connection = thrift.createConnection('localhost', 8585, {
   transport: thrift.TBufferedTransport,
   protocol: thrift.TBinaryProtocol
}).on('error', function(error) {
   console.log(error);
}).on("connect", function() {
   var client = thrift.createClient(helloSvc, connection);
   var promise = client.getMessage("Thurston Howell");
   console.log("Promise fulfilled?: " + promise.isFulfilled());
   console.log("Promise rejected?: " + promise.isRejected());
   console.log("Promise pending?: " + promise.isPending());
   promise.then(function(result) {
      console.log("Msg from server: " + result);
      console.log("Promise state: " + promise.inspect().state);
   }, function(error) {
      console.log("Error from server: " + error);
      console.log("Promise state: " + promise.inspect().state);
   });
   
   var promises = [];
   for (var i = 0; i < 5; i++) {
      promises.push(client.getMessage(""+i));
   }
   Q.all(promises).then(function(result) {
      console.log("Result after all promises complete: " + result);
   }).catch(function(error) {
      console.log("Fail after all promises complete: " + error);
   }).finally(function(){
      console.log("Finally is always called, whether sucess or failure");
      connection.end();
   });
});

