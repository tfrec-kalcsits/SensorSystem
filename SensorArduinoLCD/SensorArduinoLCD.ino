//Sensor Core classes
#include <tslsensor.h>
#include <mlxsensor.h>
#include <radiotransmitter.h>

//Networking classes
#include <packet.h>
#include <rf24radiotransmitter.h>

//LCD library from Adafruit
#include <Adafruit_RGBLCDShield.h>

using namespace sensorsystem;

//Write pipe address for RF24. Set this to one of the six read pipes of the Hub receiver radio
//Change first byte to a number from 1-6 to change the pipe
const byte pipe[6] = "1Node";

RadioTransmitter * radio;

//Sensors to read from. By default we use:
//The MLX90614 IR Sensor for temperature
//The TSL2561 Light Sensor for light measurements
MLXSensor temp_sensor;
TSLSensor light_sensor;

//This is the class for the LCD shield we'll be using as our display
Adafruit_RGBLCDShield lcd;

//Each sensor can specify a signature to be recorded with measurements.
//The signature is a C string of up to size 10.
char signature[10];

void setup() {
    //set up the devices to be used
    radio = new RF24RadioTransmitter(7,8,pipe);
    temp_sensor.begin();
    light_sensor.begin();

    //load the signature from EEPROM
    loadSignature(signature);

    //initialize the LCD Shield
    lcd.begin(16, 2);

    //Print the boot message
    lcd.print("     HELLO!");
    delay(2000);
    printMainScreenTemplate();
}

//This prints the main screen without filling the sensor values
//Output will look like: 
//A:
//O:      L:
void printMainScreenTemplate() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A\nO:      L:");
}

//Fills the main screen with temperature values
void fillMainScreenValues(float ambient, float object, float lux) {
  lcd.setCursor(2, 0);
  lcd.print(ambient, 2);
  lcd.setCursor(2,1);
  lcd.print(object);
  lcd.setCursor(11, 1);
  lcd.print(lux);
}

void loop() {
  //get readings and display to screen
  float ambient = temp_sensor.getAmbientTemperature();
  float object = temp_sensor.getObjectTemperature();
  float lux = light_sensor.getLux();
  fillMainScreenValues(ambient, object, lux);
  
  //when the user presses select, move to the options menu
  if(lcd.readButtons() & BUTTON_SELECT)
  {
    optionsMenu();
    printMainScreenTemplate();
  }
  fillMainScreenValues(ambient, object, lux);
  delay(1000);
}

void optionsMenu() {
  enum Option { LOG, UPLOAD, CONNECT, DISCONNECT, TEST, SIGNATURE, RETURN };
  for(Option option = LOG; option != RETURN;) {
    lcd.clear();
    lcd.setCursor(0,0);
    switch(option) {
      case LOG: lcd.print("   < LOG >");
        break;
      case UPLOAD: lcd.print(" < UPLOAD > ");
        break;
      case CONNECT: lcd.print(" < CONNECT >");
        break;
      case DISCONNECT: lcd.print("< DISCONNECT >");
        break;
      case TEST: lcd.print("   < TEST >");
        break;
      case SIGNATURE: lcd.print("< SIGNATURE >");
        break;
      case RETURN: lcd.print("< RETURN >");
        break;
    }

    uint8_t button;
    do {
      button = lcd.readButtons();
    }while(!(button & BUTTON_LEFT || button & BUTTON_RIGHT || button & BUTTON_SELECT));
    if(button &  BUTTON_LEFT)
      option = option == LOG ? RETURN : option - 1;
    else if (button & BUTTON_RIGHT)
      option = option == RETURN ? LOG : option + 1;
    else
      switch(option) {
        case LOG: log();
          break;
        case UPLOAD: upload();
          break;
        case CONNECT: connect();
          break;
        case DISCONNECT: disconnect();
          break;
        case TEST: test();
          break;
        case SIGNATURE: resetSignature();
          break;
        case RETURN: break;
      }
  }
}

