//PNWF Node.js Fish Price Dump
var Thrift = require('thrift');
var TradeHistory = require('./gen-nodejs/TradeHistory.js');
var tradeUtils = require('./tradeUtils.js');

var intId1 = null;
var intId2 = null;

//Connect to the server and setup a TradeHistory client
var connection = Thrift.createConnection('localhost', 8585, {
  transport: Thrift.TFramedTransport,
  protocol: Thrift.TBinaryProtocol
}).on('error', function(err) {
  console.log(err);
  clearInterval(intId1);
  clearInterval(intId2);
});
var client = Thrift.createClient(TradeHistory, connection);

//Request trade info every 4 seconds and display result
intId1 = setInterval((function() { 
  var counter = 0;
  return function() {
    var fish = ["Halibut", "Salmon", "Ono", "Tuna"][++counter%4];
    client.GetLastSale(fish, function(error, success) {
      if (success) {
        tradeUtils.logTrade(success); 
      }
    });
  };
})(), 4000);

//Request trade list info every 15 seconds and display result
intId2 = setInterval(function() {
  client.GetLastSaleList(["Halibut", "Salmon", "Ono", "Tuna"], false, function(error, success) {
    if (success) {
      for (var fish in success) {
        tradeUtils.logTrade(success[fish]); 
      }
    } else {
      console.log(error);
    }
  });
}, 15000);


