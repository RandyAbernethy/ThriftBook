<?php
  if($_POST['hello_form'] == "Submit") {
    $uname = $_POST['user_name'];
  } else {
    $uname = "Anonymous";
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
    <div><?php echo "Hello $uname"; ?></div>
  </body>
</html>

