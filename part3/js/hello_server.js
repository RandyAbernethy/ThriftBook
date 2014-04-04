//Simple Apache Thrift Server for Node.js

//Import Apache Thrift support
var fs = require("fs");
var Thrift = require('thrift');
var TBufferedTransport = require('thrift/lib/thrift/transport').TBufferedTransport;
var TJSONProtocol = require('thrift/lib/thrift/protocol').TJSONProtocol;

//Import IDL Compiler generated support for hello service
var hello_svc = require('./gen-nodejs/hello_svc.js');

//Define the hello service behavior
var hello_handler = {
  counter: 0,
  get_message: function(name, result) {
  	this.counter++;
  	var msg = "" + this.counter + ") Hello " + name + "!";
    console.log(msg);
    result(null, msg);
  }
}

//Setup the I/O stack options for the hello service
var hello_svc_opt = {
	transport: TBufferedTransport,
	protocol: TJSONProtocol,
	cls: hello_svc,
	handler: hello_handler
};

//Define the services the server will support
var server_opt = {
	staticFilePath: ".",
//	tlsOptions: {
//      key: fs.readFileSync("sec/key.pem"),
//      cert: fs.readFileSync("sec/cert.pem")
//    },
	services: {
		"/hello": hello_svc_opt
	}
}

//Create a server to server files and support Apache Thrift services
var server = Thrift.createStaticHttpThriftServer(server_opt);
var port = 9099;
server.listen(port);
console.log("Http/Thrift Server running on port: " + port);

