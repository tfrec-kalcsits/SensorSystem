#!/bin/bash

if [ ! $# -eq 1 ]; then
    echo 'Incorrect number of arguments.'
    echo 'setup_arduino.sh <arduino library directory>'
    exit 1
fi

lib_path="$1"
thirdparty=../thirdparty

if [ ! -d "$lib_path" ]; then
    echo "$lib_path is not a path. Please specify the path to arduino libraries."
    exit 1
fi

echo "Installing Adafruit_Sensor library"
rsync -a $thirdparty/Adafruit_Sensor "$lib_path/"
echo "Installing Adafruit_TSL2561 library"
rsync -a $thirdparty/Adafruit_TSL2561 "$lib_path/"
echo "Installing Adafruit-MLX90614 library"
rsync -a $thirdparty/Adafruit-MLX90614-Library "$lib_path/"
echo "Installing SensorCore library"
rsync -a . "$lib_path/"
exit 0