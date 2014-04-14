var thrift = require('thrift');                         
var helloSvc = require('./gen-nodejs/helloSvc');    

//ServiceHandler: Implement the hello service 
var helloHandler = {                        
  getMessage: function(name, result) {             
    var msg = "Hello " + name + "!";
    console.log(msg);
    result(null, msg);     
  }                                 
}                                   

//ServiceOptions: The I/O stack for the service
var helloSvcOpt = {                                 
    handler: helloHandler,                              
    processor: helloSvc,                                
    protocol: thrift.TJSONProtocol,                     
    transport: thrift.TBufferedTransport            
};                                  

//ServerOptions: Define server features
var serverOpt = {                               
    filePath: ".",                        
    services: {"/hello": helloSvcOpt},
    cors: {"http://localhost:9098": true},
    headers: {"Content-Security-Policy": 
                 "default-src 'self'; connect-src http://localhost:9099"}
}                                   

//Create and start the web server
var port = process.argv[2];
thrift.createWebServer(serverOpt).listen(port);                                 
console.log("Http/Thrift Server running on port: " + port);
console.log("Serving files from: " + __dirname);

