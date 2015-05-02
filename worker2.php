<?php

require './Res.php';


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
            $command = "./pyramic " . $file . " " . $comparedFile . " " . $_POST['ratio'];
            exec($command, $output);
            $val = $output[0];
            if ($val == 1) {
                $r = new Res($allFiles[$pic], 1);
                array_push($results, $r);
            }
            unset($output);
        }
    }

    echo(json_encode($results));
}
