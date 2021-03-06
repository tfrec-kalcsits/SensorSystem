#include <tslsensor.h>
#include <mlxsensor.h>
#include <radiotransmitter.h>
#include <packet.h>
#include <rf24radiotransmitter.h>
#include <Adafruit_RGBLCDShield.h>

using namespace sensorsystem;

/************************ USER CONFIGURATION ************************/
//Write pipe address for RF24. Set this to one of the six read pipes
//of the Hub receiver radio. Change the first byte to a number 1-6 to
//change the pipe.
const byte pipe[6] = "1Node";

//Each sensor can specify a signature to be recorded with measurements.
//The signature is a C string of up to size 10;
char signature[10];

//This sets the scale that the temperature sensor will use.
//The options are:
//TempSensor::Scale::FARENHEIT
//TempSensor::Scale::CELSIUS
//TempSensor::Scale::KELVIN
TempSensor::Scale scale = TempSensor::Scale::CELSIUS;

/********************** END USER CONFIGURATION ********************/

RadioTransmitter * radio;
MLXSensor temp_sensor;
TSLSensor light_sensor;

Adafruit_RGBLCDShield lcd;



void setup()
{
  Serial.begin(9600);
  // setup hardware devices
  radio = new RF24RadioTransmitter(7, 8, pipe);
  temp_sensor.begin();
  temp_sensor.setScale(scale);
  light_sensor.begin();
  lcd.begin(16, 2);

  //load the signature from memory
  loadSignature(signature);

  //print the boot message
  lcd.print("     HELLO!");
  delay(2000);
  initMainScreen(lcd);
}

void loop()
{
  //The main screen displays temperature readings
  float ambient = temp_sensor.getAmbientTemperature();
  float object = temp_sensor.getObjectTemperature();
  float lux = light_sensor.getLux();
  printMainScreenMeasurements(lcd, ambient, object, lux);
  if(lcd.readButtons() & BUTTON_SELECT)
  {
    runMainMenu(lcd, *radio, ambient, object, lux);
    initMainScreen(lcd);
    printMainScreenMeasurements(lcd, ambient, object, lux);
  }
  delay(1000);
}
