<?php

//require './Res.php';

//$_POST['id'] = "107702.png";

if (isset($_POST['id']) && $_POST['id'] != "") {
    $file = "./dataset/" . $_POST['id'];

    $allFiles = scandir("./dataset");
    unset($allFiles[0]);
    unset($allFiles[1]);
    unset($allFiles[2]);

    $filesIndexes = array_rand($allFiles, 227);

    $results = array();

    foreach ($filesIndexes as $pic) {
        if ("./dataset/" . $allFiles[$pic] != $file) {
            $comparedFile = "./dataset/" . $allFiles[$pic];
            $command = "./domColors " . $file . " " . $comparedFile;
            exec($command, $output);
            $val = $output[0];
            if ($val >= 0.1) {
                $r = new Res($allFiles[$pic], $val);
                array_push($results, $r);
            }
            unset($output);
        }
    }

    echo(json_encode($results));
}
