//This is a port of the MainMenu.ino file of SensorArduinoLCD
//Unlike arduino, The only publically exposed function is runMainMenu
#pragma once

#include "lcd.h"
#include <radiotransmitter.h>
#include <string>

namespace sensorsystem
{

void runMainMenu(int lcd_handle, RadioTransmitter& radio, float ambient, float object, float lux, const std::string& signature);

}