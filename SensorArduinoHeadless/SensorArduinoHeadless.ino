//Sensor Core classes
#include <tslsensor.h>
#include <mlxsensor.h>
#include <radiotransmitter.h>

//Networking classes
#include <packet.h>
#include <rf24radiotransmitter.h>

using namespace sensorsystem;

#define MILLI_PER_MINUTE 60000.0f

/************************** BEGIN USER CONFIGURATION **********************************************/

//interval in minutes that the sensor will make a recording
const float log_interval = 0.5f;

//ce and csn pins for the RF24. Set these to wherever the pins are plugged in on the board
const uint16_t ce_pin = 7;
const uint16_t csn_pin = 8;

//Write pipe address for RF24. Set this to one of the six read pipes of the Hub receiver radio
//Change first byte to a number from 1-6 to change the pipe
const byte pipe[6] = "1Node";

//Each sensor can specify a signature to be recorded with measurements.
//The signature is a C string of up to size 10.
//Reset this line to set a custom signature.
const char signature[10] = "ARDUINO";

//This sets the scale that the temperature sensor will use.
//The options are:
//TempSensor::Scale::FARENHEIT
//TempSensor::Scale::CELSIUS
//TempSensor::Scale::KELVIN
const TempSensor::Scale scale = TempSensor::Scale::CELSIUS;

/********************* END USER CONFIGURATION ***************************************************/

RadioTransmitter * radio;

//Sensors to read from. By default we use:
//The MLX90614 IR Sensor for temperature
//The TSL2561 Light Sensor for light measurements
MLXSensor temp_sensor;
TSLSensor light_sensor;

void setup() {
  //temp_sensor.begin() and light_sensor.begin() need to be called in order to initialize I2C communication
  radio = new RF24RadioTransmitter(7, 8, pipe); 
  temp_sensor.begin();
  temp_sensor.setScale(scale);
  light_sensor.begin();

  //Initialize Serial communication. This will be used for debugging purposes.
  Serial.begin(9600);
  Serial.print("beginning");
}

void loop() {
  //For each record interval, we'll make a log request to the Hub
  float ambient = temp_sensor.getAmbientTemperature();
  float object = temp_sensor.getObjectTemperature();
  float lux = light_sensor.getLux();

  Packet packet;
  packet.ambient_temperature = ambient;
  packet.object_temperature = object;
  packet.flag = Packet::Flag::LOG;
  packet.lux = lux;
  int i;
  for(i = 0; i < 10 && signature[i] != '\0'; i++)
    packet.signature[i] = signature[i];
  packet.signature[i] = '\0';

  bool success = radio->sendPacket(packet);

  //print data for debugging purposes
  Serial.println("===============================");
  Serial.print("SENT: "); Serial.println(success ? "success" : "failed");
  Serial.print("OBJECT: "); Serial.println(object);
  Serial.print("AMBIENT: "); Serial.println(ambient);
  Serial.print("LUX: "); Serial.println(lux);
  
  //wait for the interval time to make another request
  delay((int)(log_interval * MILLI_PER_MINUTE));
}
