<?php
header('Content-Type: application/json; charset=utf-8');
$allFiles = scandir("./dataset");
unset($allFiles[0]);
unset($allFiles[1]);
unset($allFiles[2]);

$selectedFiles = array_rand($allFiles, 16);
$myfiles = array();
$i = 0;
foreach ($selectedFiles as $value) {
    $myfiles[$i] = $allFiles[$value];
    $i++;
}
echo json_encode($myfiles);