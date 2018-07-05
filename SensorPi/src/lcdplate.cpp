#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>
#include <pisensor/lcdui.h>

namespace sensorsystem
{

LCDPlate::LCDPlate(int address) 
	: address(address), handle(lcdInit(2, 16, 4, RS, E, DB4, DB5, DB6, DB7, 0,0,0,0))
{
	mcp23017Setup(BASE, 0x20);
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);

	for (int i = 0; i <= 4; i++)
	{
		pinMode(BASE + i, INPUT);
		pullUpDnControl(BASE + i, PUD_UP);
	}

	pinMode(RW, OUTPUT);
	digitalWrite(RW, LOW);
}

bool LCDPlate::isButtonPressed(Button button) const
{
	return digitalRead(button) == HIGH;
}

void LCDPlate::print(std::string output) const
{
	lcdPuts(handle, output.c_str());
}

void LCDPlate::move(int row, int col) const
{
	lcdPosition(handle, row, col);
}

void LCDPlate::clear() const
{
	lcdClear(handle);
}

}
