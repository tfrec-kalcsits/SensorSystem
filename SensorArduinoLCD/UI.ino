//This file provides helper functions for using the Adafruit_RGBLCDShield

//Initializes the main screen of the application
void initMainScreen(Adafruit_RGBLCDShield& lcd)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A:");
  lcd.setCursor(0,1);
  lcd.print("O:      L:");
}

//Fills the main screen with sensor readings
void printMainScreenMeasurements(Adafruit_RGBLCDShield& lcd, float ambient, float object, float lux)
{
  lcd.setCursor(2, 0);
  lcd.print(ambient, 2);
  lcd.setCursor(2, 1);
  lcd.print(object, 2);
  lcd.setCursor(10, 1);
  lcd.print(lux, 2);
}

uint8_t waitForInput(Adafruit_RGBLCDShield& lcd)
{
  uint8_t input;
  while((input = lcd.readButtons()) == 0);
  waitForRelease(lcd);
  return input;
}

void waitForRelease(Adafruit_RGBLCDShield& lcd)
{
  while(lcd.readButtons());
}

