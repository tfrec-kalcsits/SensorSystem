//This is a test driver for the LCDPlate class.

#include <sensorpi/lcdplate.h>
#include <wiringPi.h>
#include <iostream>
#include <string>

using namespace sensorsystem;
using std::cout;
using std::endl;
using std::string;

void printWhenPressed(LCDPlate& lcd, string message, LCD::Button button)
{
    cout << message << endl;
    lcd.clear();
    lcd.home();
    lcd.print(message);
    while(lcd.isButtonPressed(button));
}

int main()
{
    LCDPlate lcd;
    lcd.print("TESTING");
    while(true)
    {
        if(lcd.isButtonPressed(lcd.UP))
            printWhenPressed(lcd, "UP", lcd.UP);
        else if(lcd.isButtonPressed(lcd.DOWN))
            printWhenPressed(lcd, "DOWN", lcd.DOWN);
        else if(lcd.isButtonPressed(lcd.LEFT))
            printWhenPressed(lcd, "LEFT", lcd.LEFT);
        else if(lcd.isButtonPressed(lcd.RIGHT))
            printWhenPressed(lcd, "RIGHT", lcd.RIGHT);
        else if(lcd.isButtonPressed(lcd.SELECT))
            printWhenPressed(lcd, "UP", lcd.SELECT);

    }
    return 0;
}