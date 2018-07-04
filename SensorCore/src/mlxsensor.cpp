#include "mlxsensor.h"

#ifdef ARDUINO
    #include <Wire.h>
#else
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
#endif

namespace sensorsystem
{

MLXSensor::MLXSensor(uint8_t address) : address(address) {}

void MLXSensor::begin()
{
	#ifdef ARDUINO
        Wire.begin();
    #else
		fd = wiringPiI2CSetup(address);
	#endif
}

float MLXSensor::getAmbientTemperature()
{
    return readTemperature(Temperature::AMBIENT);
}

float MLXSensor::getObjectTemperature()
{
    return readTemperature(Temperature::OBJECT);
}

float MLXSensor::readTemperature(Temperature type)
{
    #ifdef ARDUINO
		uint16_t data;
        Wire.beginTransmission(address);
        Wire.write(static_cast<uint8_t>(type));
        Wire.endTransmission(false);

        Wire.requestFrom(address, (uint8_t)3);
        data = (Wire.read()) | (Wire.read() << 8);

        uint8_t extra = Wire.read();

        float temp = (float)data * 0.02;

    #else
		float temp = wiringPiI2CReadReg16(fd, static_cast<int>(type)) * 0.02;
    #endif
    
    if(scale != Scale::KELVIN)
		temp -= 273.15;
    if(scale == Scale::FARENHEIT)
        temp = (temp * 9 / 5) + 32;
    return temp;
}

}
