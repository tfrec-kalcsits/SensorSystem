# Configuring the Raspberry Pis

Some Configurations will need to be performed on the Raspberry Pis before the Software can be installed.
This walkthrough will take you through all the steps you need to setup the Raspberry Pis for use as a
Sensor and a Hub. This tutorial will assume that you've installed the latest version of the Raspbian 
operation system on the Raspberry Pi.

## 1. Sensor

In order to use the Raspberry Pi as a sensor, you will have to enable the I2C and SPI protocols on the 
Raspberry Pi. To do so, go to the dropdown menu in the upper left hand corner and go to Raspberry Pi 
Configuration. Here you will see a tab called Interfaces. Make sure that I2C and SPI are selected. You may 
be prompted to restart your device before you can continue.

## 2. Hub

Do the same as in step 1. There is some additional configuration required.

You will first need to setup the real time clock. To do so, type the following command:

```
sudo nano /boot/config.txt
```

This will open a text editor to edit the file /boot/config.txt. In this file, add the following line:

```
dtoverlay=i2c-rtc,ds1307
```

Once this is done, type CTRL + X and press y to save your changes.

Next, type the following commands:

```
sudo apt-get -y remove fake-hwclock
sudo update-rc.d -f fake-hwclock remove
sudo nano /lib/udev/hwclock-set
```

You will be back in the nano text editor editing the file /lib/udev/hwclock-set. Find these 3 lines and
place a # sign in front of them to comment them out:

```
if [ -e /run/systemd/system ]; then
    exit 0
fi
```

The final result should look like this:

```
#if [ -e /run/systemd/system ]; then
#    exit 0
#fi
```

Make sure that your Raspberry Pi is connected to the internet and the time is setup correctly. We need to 
sync up the time on the real time clock with the time from the Raspberry Pis servers. To do this, run the
following commmand:

```
sudo hwclock -w
```

This should be all you need to set up the real time clock.

TODO: setting up the 3G connection