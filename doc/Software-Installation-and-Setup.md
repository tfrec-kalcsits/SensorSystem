# Software Installation and Setup

All the software needed for the SensorSystem should be hosted on Github. You will need to install some
dependencies separately but all of these should be in the Raspberry Pis package manager.

## 1. Headless Arduino Sensor

To install the software for the Headless Arduino Sensor, you will first need to install the official
Arduino IDE. Once this is done, find the location that Arduino installed the libraries directory. On 
Windows, this will be in Documents.

Download the software from Github either directly or using git. You will need to copy some folders from 
the repository into the library directory for Arduino. These are as follows:

```
thirdparty/Adafruit_Sensor
thirdparty/Adafruit_TSL2561
thirdparty/RF24
SensorCore
Networking
```

Once these are copied, open SensorArduinoHeadless/SensorArduinoHeadless.ino in the Arduino IDE. A few 
configurations should be made before compiling and uploading. Details on these can be found in           [4. Software Configurations](./Software-Configurations.md). Once these configurations are complete, compile and upload the program to the arduino. This is all you should need to do.

## 2. Arduino Sensor with LCD Screen

The process to install this is exactly the same as part 1, but one more folder must be copied to the library directory for Arduino. This is:

```
thirdparty/Adafruit-RGB-LCD-Shield-Library
```

Once this is done, follow the same process but with the file SensorArduinoLCD/SensorArduinoLCD.ino

## 3. Raspberry Pi Sensor

The build and install process for the Raspberry Pi portion of the software is done using CMake. To install all the necessary prerequisites to build the software, type the following commands:

```
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install -y libncurses5-dev libcurl4-openssl-dev wiringpi i2c-tools libi2c-dev cmake
```

Once the needed dependencies are installed, type the following commands in the root folder of SensorSystem:

```
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

After the software is finished installing, you should be good to go! To launch the software, type the command:

```
sudo sensorsystem-sensor
```

This will launch the sensor program. To launch the program on boot, type

```
sudo nano /etc/rc.local
```

to open the nano text editor. in this file, type the following before the line "exit 0":

```
sensorsystem-sensor &
```

Use CTRL+X and y to exit. Then type the commmand:

```
sudo chmod +x /etc/rc.local
```

reboot your Raspberry Pi to test. The sensor application should start on boot.

## 4. Hub

The setup process for the Hub is largely the same as the Sensor. The only difference is the name of the
program to call. Instead of sensorsystem-sensor, call sensorsystem-hub. Also, in /etc/rc.local, make sure
to place sensorsystem-hub & instead of sensorsystem-sensor &.

This should be all you need to get started! For configuring the software, please see the next page

[Next: Software Configurations](./Software-Configurations.md)

[Prev: Configuring the Raspberry Pis](./Configuring-the-Raspberry-Pis.md)

