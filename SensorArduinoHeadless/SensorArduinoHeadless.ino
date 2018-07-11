//Sensor Core classes
#include <tslsensor.h>
#include <mlxsensor.h>
#include <radiotransmitter.h>

//Networking classes
#include <packet.h>
#include <rf24radiotransmitter.h>

//EEPROM library to be used for reading and writing persistent data
#include <EEPROM.h>

using namespace sensorsystem;

//ce and csn pins for the RF24. Set these to wherever the pins are plugged in on the board
uint16_t ce_pin = 7;
uint16_t csn_pin = 8;

//Write pipe address for RF24. Set this to one of the six read pipes of the Hub receiver radio
//Change first byte to a number from 1-6 to change the pipe
byte pipe[6];

RadioTransmitter * radio;

//Sensors to read from. By default we use:
//The MLX90614 IR Sensor for temperature
//The TSL2561 Light Sensor for light measurements
MLXSensor temp_sensor;
TSLSensor light_sensor;

//Each sensor can specify a signature to be recorded with measurements.
//The signature is a C string of up to size 10.
//Reset this line to set a custom signature.
char signature[10];

void setup() {
  Serial
}