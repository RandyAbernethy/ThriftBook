<?php
  require 'vendor/autoload.php';
  require 'gen-php/helloSvc.php';

  $msg = 'No server response';

  if ($_SERVER['REQUEST_METHOD'] === 'POST' && 
      array_key_exists('hello_form', $_POST) && 
      $_POST['hello_form'] == "Submit") {
    try {
      $trasn_ep = new Thrift\Transport\TSocket('localhost', 9095);
      $trans_buf = new Thrift\Transport\TBufferedTransport($trasn_ep);
      $proto = new Thrift\Protocol\TBinaryProtocol($trans_buf);
      $client = new helloSvcClient($proto);

      $trasn_ep->open();
      $msg = $client->getMessage($_POST['user_name']);
      $trasn_ep->close();
    } catch (Thrift\Exception\TException $tx) {
      error_log( 'TException: '.$tx->getMessage()."\n" );
    }
  }
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Hello Thrift</title>
  </head>
  <body>
    <form name="hello_form" method="post" action="hello_client.php">
      Name: 
      <input type="text" name="user_name">
      <input type="submit" name="hello_form" value="Submit">
    </form>
    <br>
    <div><?php echo "$msg"; ?></div>
  </body>
</html>

