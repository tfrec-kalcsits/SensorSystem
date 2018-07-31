#include <sensorpi/ui.h>
#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>

//functions taken from lcd-adafruit.c in wiringPi

namespace sensorsystem
{

static void setBacklightColour (int colour)
{
  colour &= 7 ;

  digitalWrite (AF_RED,   !(colour & 1)) ;
  digitalWrite (AF_GREEN, !(colour & 2)) ;
  digitalWrite (AF_BLUE,  !(colour & 4)) ;
}

static int adafruitLCDSetup (int colour)
{
  int i ;

  pinMode (AF_RED,   OUTPUT) ;
  pinMode (AF_GREEN, OUTPUT) ;
  pinMode (AF_BLUE,  OUTPUT) ;
  setBacklightColour (colour) ;

  for (i = 0 ; i <= 4 ; ++i)
  {
    pinMode (AF_BASE + i, INPUT) ;
    pullUpDnControl (AF_BASE + i, PUD_UP) ;
  }

  pinMode (AF_RW, OUTPUT) ; digitalWrite (AF_RW, LOW) ;

  return lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) ;
}

int initLCD()
{
    mcp23017Setup(AF_BASE, 0x20);
    return adafruitLCDSetup(7); 
}

void initMainScreen(int handle)
{
    lcdClear(handle);
    lcdHome(handle);
    lcdPuts(handle, "A:");
    lcdPosition(handle, 0, 1);
    lcdPuts(handle, "O:      L:");
}

void printMainScreenMeasurements(int handle, float ambient, float object, float lux)
{
    lcdPosition(handle, 2, 0);
    lcdPrintf(handle, "%.2f", ambient);
    lcdPosition(handle, 2, 1);
    lcdPrintf(handle, "%.2f", object);
    lcdPosition(handle, 10,1);
    lcdPrintf(handle, "%.1f", lux);
}

bool isButtonPressed(int handle, uint8_t button)
{
    return digitalRead(button) == LOW;
}

void waitForRelease(int handle)
{
    while(isButtonPressed(handle, AF_UP)
        || isButtonPressed(handle, AF_DOWN)
        || isButtonPressed(handle, AF_LEFT)
        || isButtonPressed(handle, AF_RIGHT)
        || isButtonPressed(handle, AF_SELECT));
}

uint8_t waitForInput(int handle)
{
    for(;;)
    {
        if(isButtonPressed(handle, AF_UP))
            return AF_UP;
        if(isButtonPressed(handle, AF_DOWN))
            return AF_DOWN;
        if(isButtonPressed(handle, AF_RIGHT))
            return AF_RIGHT;
        if(isButtonPressed(handle, AF_LEFT))
            return AF_LEFT;
        if(isButtonPressed(handle, AF_SELECT))
            return AF_SELECT;
	}
}

}
