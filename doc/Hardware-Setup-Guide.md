# Hardware Setup Guide

This page will show take you through the steps of setting up the necessary hardware for the various components of the sensor system.

## 1. Headless Arduino Sensor

The Headless Arduino Sensor is meant to be placed out in fields for extended periods of time and takes measurements in predetermined intervals.
No user interaction is required to run one of these units. As soon as it turns on, it will start to take measurements and will keep taking
measurements until the system is shut off.

To build this, we need the following materials:

* nRF24l01+ RF radio transmitter  - [link](https://www.aliexpress.com/item/Smart-Electronics-1Set-2-4G-1100-Meters-Long-Distance-NRF24L01-PA-LNA-Wireless-Transceiver-Communication-Modules/32707423150.html?spm=2114.search0104.3.1.2f3679daNLhNiN&ws_ab_test=searchweb0_0,searchweb201602_1_10065_10068_204_10130_318_10547_10546_10059_10884_10548_10545_10887_10696_100031_10084_10083_10103_10618_452_10307_532,searchweb201603_60,ppcSwitch_0&algo_expid=3c7fee1b-fa24-4b2b-a946-42887456755f-0&algo_pvid=3c7fee1b-fa24-4b2b-a946-42887456755f&transAbTest=ae803_5&priceBeautifyAB=0)
* Arduino Uno Rev 3 - [link](https://www.aliexpress.com/item/Smart-Electronics-1Set-2-4G-1100-Meters-Long-Distance-NRF24L01-PA-LNA-Wireless-Transceiver-Communication-Modules/32707423150.html?spm=2114.search0104.3.1.2f3679daNLhNiN&ws_ab_test=searchweb0_0,searchweb201602_1_10065_10068_204_10130_318_10547_10546_10059_10884_10548_10545_10887_10696_100031_10084_10083_10103_10618_452_10307_532,searchweb201603_60,ppcSwitch_0&algo_expid=3c7fee1b-fa24-4b2b-a946-42887456755f-0&algo_pvid=3c7fee1b-fa24-4b2b-a946-42887456755f&transAbTest=ae803_5&priceBeautifyAB=0)
* MLX90614 Infrared Sensor - [link](https://www.aliexpress.com/item/GY-906-MLX90614ESF-New-MLX90614-Contactless-Temperature-Sensor-Module-For-Arduino-Compatible/32739146147.html?spm=2114.search0104.3.2.699934faknjlBa&ws_ab_test=searchweb0_0,searchweb201602_1_10065_10068_204_10130_318_10547_10546_10059_10884_10548_10545_10887_10696_100031_10084_10083_10103_10618_452_10307_532,searchweb201603_60,ppcSwitch_0&algo_expid=b6f632e5-2b26-40f9-8b8c-7be8477b249a-0&algo_pvid=b6f632e5-2b26-40f9-8b8c-7be8477b249a&transAbTest=ae803_5&priceBeautifyAB=0)
* TSL2561 Light Sensor - [link](https://www.adafruit.com/product/439?gclid=Cj0KCQjw9NbdBRCwARIsAPLsnFZvBKCgYZUCkA_8lXJjnvWD5JT4TLO_xhLZNdWYmtnD803pbOtHs5oaAqeMEALw_wcB)
* Mini breadboard - [link](https://www.aliexpress.com/item/SYB-170-Mini-Solderless-Prototype-Experiment-Test-Breadboard-170-Tie-points-35-47-8-5mm-for/32902041277.html?spm=2114.search0104.3.25.51fd3b3cxxuOZY&ws_ab_test=searchweb0_0,searchweb201602_1_10065_10068_204_10130_318_10547_10546_10059_10884_10548_10545_10887_10696_100031_10084_10083_10103_10618_452_10307_532,searchweb201603_60,ppcSwitch_0&algo_expid=3d998bfd-504e-4784-a5b7-4aeccdad269d-4&algo_pvid=3d998bfd-504e-4784-a5b7-4aeccdad269d&transAbTest=ae803_5&priceBeautifyAB=0)
* A standard portable battery (can be found at most department stores)

First start by connecting the mini breadboard to the Arduino. The mini breadboard will be used to wire out the i2c pins to the MLX90614 and the TSL2561
