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

echo "Installing RF24 library"
rsync -a "$thirdparty/RF24" "$lib_path/"
echo "Installing Networking library"
rsync -a . "$lib_path/SensorSystem-Networking"
exit 0