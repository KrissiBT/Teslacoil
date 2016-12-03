<?php
$file = 'stat.txt';
// Open the file to get existing content
$current = file_get_contents($file);
// Append a new person to the file
if ($current == "1") {
  $current = "0";
  // Write the contents back to the file
  file_put_contents($file, $current);
}
else {
  $current = "1";
  // Write the contents back to the fil
  file_put_contents($file, $current);

}
?>
