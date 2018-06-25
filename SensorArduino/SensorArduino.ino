//Sensor Core classes
#include <sensorcore.h>
#include <measurement.h>
#include <tslsensor.h>
#include <mlxsensor.h>

//Networking classes
#include <packet.h>
#include <rf24radiotransmitter.h>

using namespace sensorsystem;

#define MILLI_PER_MINUTE 60000.0f 

//interval in minutes that the sensor will make a recording
float log_interval = 0.5f;

//ce and csn pins for the RF24. Set these to wherever the pins are plugged in on the board
uint16_t ce_pin = 7;
uint16_t csn_pin = 8;

//Write pipe address for RF24. Set this to one of the six read pipes of the Hub receiver radio
//Change first byte to a number from 1-6 to change the pipe
byte pipe[6] = "1Node";

//By default we use the RF24 as our radio transmitter
RF24RadioTransmitter radio(ce_pin, csn_pin, pipe);

//Sensors to read from. By default we use:
//The MLX90614 IR Sensor for temperature
//The TSL2561 Light Sensor for light measurements
MLXSensor temp_sensor;
TSLSensor light_sensor;

//Each sensor can specify a signature to be recorded with measurements.
//The signature is a C string of up to size 10.
//Reset this line to set a custom signature.
char signature[10] = "FIRST";

//The core logic class of the Sensor node. This class stores
//a reference to the sensors and radio, so make sure that the
//sensor and radio objects aren't deleted or go out of scope before
//the core app does. This will lead to dangling references.
SensorCore app(temp_sensor, light_sensor, radio, signature);

void setup() {
  //temp_sensor.begin() and light_sensor.begin() need to be called in order to initialize I2C communication
  temp_sensor.begin();
  light_sensor.begin();

  //Initialize Serial communication. This will be used for debugging purposes.
  Serial.begin(9600);
}

void loop() {
  //For each record interval, we'll make a log request to the Hub
  bool success = app.makeRequest(Packet::Flag::LOG);
  Measurement measurement = app.getMeasurement();

  //print data for debugging purposes
  Serial.println("===============================");
  Serial.print("SENT: "); Serial.println(success ? "success" : "failed");
  Serial.print("OBJECT: "); Serial.println(measurement.object);
  Serial.print("AMBIENT: "); Serial.println(measurement.ambient);
  Serial.print("LUX: "); Serial.println(measurement.lux);
  
  //wait for the interval time to make another request
  delay((int)(log_interval * MILLI_PER_MINUTE));
}
