//PNWF Node.js Price Server Mock
var Thrift = require('thrift');
var TFramedTransport = require('thrift/lib/thrift/transport').TFramedTransport;
var TBinaryProtocol = require('thrift/lib/thrift/protocol').TBinaryProtocol;
var TradeTypes = require('./gen-nodejs/pnwf_trades_types.js');
var TradeHistory = require('./gen-nodejs/TradeHistory.js');
var tradeUtils = require('./pnwf_trade_utils.js');

//Mock trade support
var getMockTrade = (function() {
  next_trade_id = 1;
  return function(fish) {
    return new TradeTypes.Trade({
      fish: fish,
      date_time: tradeUtils.getTimeStamp(),
      price: ((1055 + tradeUtils.getTimeStamp().second) / 100).toFixed(2),
      amount: new TradeTypes.FishSizeUnit({pounds: 175 + (next_trade_id%12 * 20)}),
      market: (next_trade_id % 2 == 0) ? 
                TradeTypes.Market['SanFrancisco'] :
                TradeTypes.Market['Portland'],  
      id: next_trade_id++
    });
  };
})();

//TradeHistory service behavior
var TradeHistoryHandler = {
  GetLastSale: function(fish, result) {
    if (!fish) {
      result(new TradeTypes.BadFish({fish: fish, error_code: 5}), null);
    } else {
      var trade = getMockTrade(fish);
      tradeUtils.logTrade(trade);
      result(null, trade);
    }
  },
  GetLastSaleList: function(fishes, fail_fast, result) {
    if (!fishes) {
      result(new TradeTypes.BadFish({fish: "", error_code: 5}), null);
    } else if (!fail_fast && tradeUtils.getTimeStamp().second > 45) {
      var bf = {};
      for (var fish in fishes) { bf[fishes[fish]] = 7; };
      result(new TradeTypes.BadFishes({fish_errors: bf}), null);
    } else {
      var trades = [];
      for (var fish in fishes) {
        var trade = getMockTrade(fishes[fish]);
        tradeUtils.logTrade(trade);
        trades.push(trade);
      }
      result(null, trades);
    }
  }
};

//Setup and run the server
var ServerOpt = {
  protocol: TBinaryProtocol,
  transport: TFramedTransport
}
var port = 8585;
Thrift.createServer(TradeHistory, TradeHistoryHandler, ServerOpt).listen(port);
console.log("Thrift Server running on port: " + port);

