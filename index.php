<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>TeslaCoil!!!</title>
  </head>
  <body>
    <p>on</p>
  </body>
</html>
<?php
$myfile = fopen("stat.txt", "r") or die("Unable to open file!");
$info = fread($myfile,filesize("stat.txt"));
fclose($myfile);
echo $info;
?>
