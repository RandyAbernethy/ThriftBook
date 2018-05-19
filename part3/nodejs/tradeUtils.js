//PNWF Node.js Trade Utilities
var TradeTypes = require('./gen-nodejs/trade_types.js');

var getTimeStamp = exports.getTimeStamp = function() {
  var date = new Date();
  return new TradeTypes.TimeStamp({
    year: date.getFullYear(),
    month: date.getMonth(),
    day: date.getDate(),
    hour: date.getHours(),
    minute: date.getMinutes(),
    second: date.getSeconds()
  });
}

var getAmountString = exports.getAmountString = function(trade) {
  var as = "";
  if (trade.amount.pounds) {
    as = " " + trade.amount.pounds + " lbs";
  } else if (trade.amount.kilograms) {
    as = " " + trade.amount.kilograms + " kg";
  } else if (trade.amount.standard_crates) {
    as = " " + trade.amount.standard_crates + " cr";
  } else if (trade.amount.metric_tons) {
    as = " " + trade.amount.metric_tons + " tons";
  }
  return as;
}
  
var getDateTimeString = exports.getDateTimeString = function(trade) {
  return (trade.date_time.hour<10 ? "[0" : "[") + trade.date_time.hour + 
   (trade.date_time.minute<10 ? ":0" : ":") + trade.date_time.minute + 
   (trade.date_time.second<10 ? ":0" : ":") + trade.date_time.second + "]";
}

var logTrade = exports.logTrade = function(trade) {
  console.log(getDateTimeString(trade) + " " + trade.id + "." + trade.fish + 
    ", " + Object.keys(TradeTypes.Market)[trade.market] +
    getAmountString(trade) + " @ " + (+trade.price).toFixed(2));
}


