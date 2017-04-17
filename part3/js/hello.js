var thrift = require('thrift');                 	
var helloSvc = require('./gen-nodejs/helloSvc');		

//ServiceHandler: Implement the hello service 
var helloHandler = {                       	
  counter: 0,                           
  getMessage: function(name, result) {             
    this.counter++;                         
    var msg = "" + this.counter + ") Hello " + name + "!";  
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
    files: ".",                        
    services: {                         
        "/hello": helloSvcOpt                 
    }                               
}                                   

//Create and start the web server 
var server = thrift.createWebServer(serverOpt);    
var port = 9090;                            		
server.listen(port);                        		
console.log("Http/Thrift Server running on port: " + port);

