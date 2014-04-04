var Thrift = require('thrift');
var TBufferedTransport = require('thrift/lib/thrift/transport').TBufferedTransport;
var TJSONProtocol = require('thrift/lib/thrift/protocol').TJSONProtocol;
var bad_msg = require('./gen-nodejs/hello_error_types.js').bad_msg;
var hello_error = require('./gen-nodejs/hello_error.js');

var hello_handler = {
  get_message: function(name, result) {
  	if (typeof name !== "string" || name.length < 1) {
  	  var e = new bad_msg();
      e.error_code = 13;
      e.msg = "Noname";
      result(e, null);
  	} else {
      result(null, "Hello " + name + "!");
    }
  }
}

var hello_error_opt = {
	transport: TBufferedTransport,
	protocol: TJSONProtocol,
	cls: hello_error,
	handler: hello_handler
};

var server_opt = {
	staticFilePath: ".",
	services: { "/hello": hello_error_opt }
}

var server = Thrift.createStaticHttpThriftServer(server_opt);
var port = 9099;
server.listen(port);
console.log("Http/Thrift Server running on port: " + port);
console.log("Serving files from: " + __dirname);

