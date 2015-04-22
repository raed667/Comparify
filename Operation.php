<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Operation
 *
 * @author r3d
 */
class Operation extends Thread {

    private $pic;
    private $origin;

    public function __construct($origin, $pic) {

        $this->pic = $pic;
        $this->origib = $origin;
    }

    public function run() {

        if ($this->pic != $this->origin) {
            $command = "./domColors $this->origin $this->pic";
            exec($command, $output);
            $val = $output[0];
            unset($output);
            return $val;
        }
    }

}
