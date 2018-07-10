#pragma once
#include <string>


namespace sensorsystem
{

class LCDPlate
{
	public:
	enum Button { SELECT = 100, RIGHT, DOWN, UP, LEFT };

	static constexpr int base_i2c_address = 0x20;

	LCDPlate(int address=base_i2c_address);

	void home();
	bool isButtonPressed(Button button);
	void print(std::string output);
	void move(int row, int col);
	void clear();
	void setBacklight(bool on);
	
	private:
	enum GPIO { BASE = 100, RED = BASE + 6, GREEN, BLUE, DB7, DB6, DB5, DB4, E, RW, RS};

	int handle;
};

}