<?php

if (isset($_POST['id']) && $_POST['id'] != "") {
    $file = "./dataset/" . $_POST['id'];

    //echo $file;
    $allFiles = scandir("./dataset");
    unset($allFiles[0]);
    unset($allFiles[1]);
    unset($allFiles[2]);

    $filesIndexes = array_rand($allFiles, 227);

    $testRes = array();
    $testedFiles = array();


    $file1;
    $file2;
    $file3;
    $max1 = 0;
    $max2 = 0;
    $max3 = 0;
    $inter;

    foreach ($filesIndexes as $pic) {
        if ("./dataset/" . $allFiles[$pic] != $file) {
            $comparedFile = "./dataset/" . $allFiles[$pic];
            $command = "./domColors " . $file . " " . $comparedFile;
            exec($command, $output);
            $val = $output[0];
            if ($val > $max3) {
                $file3 = $allFiles[$pic];
                $max3 = $val;
                if ($val > $max2) {
                    $file3 = $file2;
                    $file2 = $allFiles[$pic];
                    $max3 = $max2;
                    $max2 = $val;

                    if ($val > $max1) {
                        $file2 = $file1;
                        $file1 = $allFiles[$pic];
                        $max2 = $max1;
                        $max1 = $val;
                    }
                }
            }

            // array_push($testRes, $output[0]);
            //array_push($testedFiles, $allFiles[$pic]);
            unset($output);
        }
    }
    /*
      $unclassed = array_map(null, $testRes, $testedFiles);

      rsort($testRes);

      $max1 = $testRes[0];
      $max2 = $testRes[1];
      $max3 = $testRes[3];

      foreach ($unclassed as $value) {
      if ($value[0] == $max1) {
      $file1 = $value[1];
      } elseif ($value[0] == $max2) {
      $file2 = $value[1];
      } elseif ($value[0] == $max3) {
      $file3 = $value[1];
      }
      } */

    echo(json_encode(array($file1, $max1, $file2, $max2, $file3, $max3)));
}