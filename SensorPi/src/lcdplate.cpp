#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>
#include <sensorpi/lcdplate.h>

namespace sensorsystem
{

LCDPlate::LCDPlate(int address) 
{
	mcp23017Setup(BASE, address);
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
	setBacklight(true);

	for (int i = 0; i <= 4; i++)
	{
		pinMode(BASE + i, INPUT);
		pullUpDnControl(BASE + i, PUD_UP);
	}

	pinMode(RW, OUTPUT);
	digitalWrite(RW, LOW);

	handle = lcdInit(2, 16, 4, RS, E, DB4, DB5, DB6, DB7, 0,0,0,0);
	clear();
	home();
}

bool LCDPlate::isButtonPressed(Button button)
{
	return digitalRead(button) == HIGH;
}

void LCDPlate::print(std::string output)
{
	lcdPuts(handle, output.c_str());
}

void LCDPlate::move(int row, int col)
{
	lcdPosition(handle, row, col);
}

void LCDPlate::clear()
{
	lcdClear(handle);
}

void LCDPlate::home()
{
	lcdHome(handle);
}

void LCDPlate::setBacklight(bool on)
{
	digitalWrite(RED, on);
	digitalWrite(GREEN, on);
	digitalWrite(BLUE, on);
}

}
