#!/bin/bash

if [ ! $# -eq 1 ]; then
    echo 'Incorrect number of arguments.'
    echo 'setup_arduino.sh <arduino library directory>'
    exit 1
fi

lib_path="$1"

if [ ! -d "$lib_path" ]; then
    echo "$lib_path is not a path. Please specify the path to arduino libraries."
    exit 1
fi

if ! hash git 2>/dev/null; then
    echo 'Error: git is not installed. Please install git before using.'
    exit 1
fi

#install TSL library from Adafruit
[[ -d "${lib_path}Adafruit_TSL2561" ]] || git clone https://github.com/adafruit/Adafruit_TSL2561.git "${lib_path}Adafruit_TSL2561"

#install the core sensor library from Adafruit
[[ -d "${lib_path}Adafruit_Sensor" ]] || git clone https://github.com/adafruit/Adafruit_Sensor.git "${lib_path}Adafruit_Sensor"

#install the SensorSystem-Networking library
[[ -d "${lib_path}SensorSystem-Networking" ]] || git clone https://github.com/tfrec-kalcsits/SensorSystem-Networking.git "${lib_path}SensorSystem-Networking"

#run the install script for SensorSystem-Networking
bash "${lib_path}SensorSystem-Networking/setup_arduino.sh" "${lib_path}"