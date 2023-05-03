#!/usr/bin/env nu

let factor = '3.5%';

def convert [file: string] {
  (run-external
    convert
      '-resize' $factor
      $'original/($file)'
      $file)
}

convert 'among-us-brown-toilet-paper-hat-png-01.png'
convert 'among-us-green-dead-body-png-01.png'
convert 'among-us-orange-egg-hat-png-01.png'
convert 'among-us-red-png-01.png'
