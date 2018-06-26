#!/bin/bash

if [ ! $# -eq 1 ]; then
    echo 'Incorrect number of arguments.'
    echo 'setup_arduino.sh <arduino library directory>'
    exit 1
fi

lib_path="$1"
thirdparty=../thirdparty
networking=../Networking
core = ../SensorCore

if [ ! -d "$lib_path" ]; then
    echo "$lib_path is not a path. Please specify the path to arduino libraries."
    exit 1
fi

sh $networking/setup_arduino.sh $lib_path
sh $core/setup_arduino.sh $lib_path
echo "SensorArduino ready for installation. Please use the Arduino IDE to compile and upload to your device."
exit 0