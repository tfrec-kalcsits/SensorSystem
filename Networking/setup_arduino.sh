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

if [ ! -d "${lib_path}RF24" ]; then
    git clone https://github.com/nRF24/RF24.git "${lib_path}RF24"
fi