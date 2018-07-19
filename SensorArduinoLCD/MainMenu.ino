#include <string.h>

//This file contains functions defining the behavior of the main menu

//An enum that represents the options of the menu
enum Option { LOG, UPLOAD, CONNECT, DISCONNECT, SIGNATURE, AUTOLOG, RETURN };

void printOption(Adafruit_RGBLCDShield& lcd, Option option);
Packet optionToPacket(Option option, float ambient, float object, float lux, char * signature);

//starts the main menu
void beginMainMenu(Adafruit_RGBLCDShield& lcd, RadioTransmitter& radio, float ambient, float object, float lux)
{
  lcd.clear();
  lcd.home();
  lcd.print("  MAIN MENU");
  waitForRelease(lcd);
  lcd.clear();
  lcd.home();
  
  Option option = LOG;
  printOption(lcd, option);

  for(;;)
  {
    uint8_t button = waitForInput(lcd);
    if(button & BUTTON_LEFT)
    {
      option = option == LOG ? RETURN : option - 1;
      printOption(lcd, option);
    }
    else if(button & BUTTON_RIGHT)
    {
      option = option == RETURN ? LOG : option + 1;
      printOption(lcd, option);
    }
    else if(button & BUTTON_SELECT)
      break;
  }

  switch(option)
  {
    case SIGNATURE:
      break;
    case AUTOLOG:
      break;
    case RETURN:
      break;
    default: radio.sendPacket(optionToPacket(option, ambient, object, lux, signature));
  }
}

void printOption(Adafruit_RGBLCDShield& lcd, Option option)
{
  lcd.clear();
  lcd.home();
  
  switch(option)
  {
    case LOG: lcd.print("    < LOG >");
      break;
    case UPLOAD: lcd.print("  < UPLOAD >");
      break;
    case CONNECT: lcd.print("  < CONNECT >");
      break;
    case DISCONNECT: lcd.print(" < DISCONNECT >");
      break;
    case SIGNATURE: lcd.print(" < SIGNATURE >");
      break;
    case AUTOLOG: lcd.print("  < AUTOLOG >");
      break;
    case RETURN: lcd.print("  < RETURN >");
  }
}

Packet optionToPacket(Option option, float ambient, float object, float lux, char * signature)
{
  Packet::Flag flag;
  switch(option)
  {
    case LOG: flag = Packet::Flag::LOG;
      break;
    case UPLOAD: flag = Packet::Flag::UPLOAD;
      break;
    case CONNECT: flag = Packet::Flag::CONNECT;
      break;
    case DISCONNECT: flag = Packet::Flag::DISCONNECT;
      break;
    default:
      break;
  }

  Packet packet;
  packet.flag = flag;
  packet.ambient_temperature = ambient;
  packet.object_temperature = object;
  packet.lux = lux;
  strncpy(packet.signature, signature, 10);
  return packet;
}



