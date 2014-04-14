(function() {
   var transport = new Thrift.TXHRTransport("http://localhost:9099/hello");
   var protocol  = new Thrift.TJSONProtocol(transport);
   var client    = new helloSvcClient(protocol);

   var nameElement = document.getElementById("name_in");
   var outputElement = document.getElementById("output");
   document.getElementById("get_msg")
      .addEventListener("click", function(){
         client.get_message(nameElement.value, function(result) {
            outputElement.innerHTML = result;
         });
      });
})();

