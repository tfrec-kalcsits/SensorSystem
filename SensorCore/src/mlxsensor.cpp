#include "mlxsensor.h"

#include <Wire.h>

namespace sensorsystem
{

MLXSensor::MLXSensor(uint8_t address) : address(address) {}

void MLXSensor::begin()
{
    Wire.begin();
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
    uint16_t data;

    Wire.beginTransmission(address);
    Wire.write(static_cast<uint8_t>(type));
    Wire.endTransmission(false);

    Wire.requestFrom(address, (uint8_t)3);
    data = (Wire.read()) | (Wire.read() << 8);

    uint8_t extra = Wire.read();

    float temp = (float)data * 0.02;
    if(scale != Scale::KELVIN)
        temp -= 273.15;
    if(scale == Scale::FARENHEIT)
        temp = (temp * 9 / 5) + 32;

    return temp;
}

}