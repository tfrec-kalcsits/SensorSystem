#include <string.h>

//This file contains functions defining the behavior of the main menu

//An enum that represents the options of the menu
enum Option { LOG, UPLOAD, CONNECT, DISCONNECT, SIGNATURE, RETURN };

void printOption(Adafruit_RGBLCDShield& lcd, Option option);
Packet optionToPacket(Option option, float ambient, float object, float lux, char * signature);

//starts the main menu
void runMainMenu(Adafruit_RGBLCDShield& lcd, RadioTransmitter& radio, float ambient, float object, float lux)
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
    case SIGNATURE: storeSignature(newSignature(lcd, signature));
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

char * newSignature(Adafruit_RGBLCDShield& lcd, char * signature)
{
  //obtains a list of all available characters
  //limited to a-z, 0-9, and space
  char characters[37];
  characters[0] = ' ';
  for(int i = 0; i < 26; i++)
    characters[i + 1] = 'a' + i;
  for(int i = 0; i <= 9; i++)
    characters[i + 27] = i + 48;

  //new signature will be stored in an int array containing indexes to characters
  int new_values[10];
  new_values[0] = 1;
  int index = 0;

  lcd.clear();
  lcd.home();
  lcd.print("SET SIGNATURE");
  lcd.setCursor(index, 1);
  lcd.print('a');
  lcd.setCursor(index, 1);
  

  for(uint8_t current_value = 1, button = waitForInput(lcd); !(button & BUTTON_SELECT); button = waitForInput(lcd))
  {
    if(button & BUTTON_LEFT && index > 0)
    {
      lcd.print(' ');
      index--;
      lcd.setCursor(index, 1);
      current_value = new_values[index];
    }
    else if(button & BUTTON_RIGHT && index < 9)
    {
      index++;
      current_value = 1;
      lcd.setCursor(index, 1);
      lcd.print(characters[current_value]);
      lcd.setCursor(index, 1);
      new_values[index] = current_value;
    }
    else if(button & BUTTON_UP)
    {
      current_value = current_value == 36 ? 0 : current_value + 1;
      lcd.print(characters[current_value]);
      lcd.setCursor(index, 1);
      new_values[index] = current_value;
    }
    else if(button & BUTTON_DOWN)
    {
      current_value = current_value == 0 ? 36 : current_value - 1;
      lcd.print(characters[current_value]);
      lcd.setCursor(index, 1);
      new_values[index] = current_value;
    }
  }
  
  for(int i = 0; i <= index; i++)
    signature[i] = characters[new_values[i]];
  if(index < 9) 
    signature[index + 1] = '\0';
  return signature;
}



