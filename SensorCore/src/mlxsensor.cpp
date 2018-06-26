#include "mlxsensor.h"

#ifdef ARDUINO
    #include <Wire.h>
#else
    #include <bcm2835.h>
    #include "i2cerror.h"
#endif

namespace sensorsystem
{

MLXSensor::MLXSensor(uint8_t address) : address(address) {}

#ifdef ARDUINO
void MLXSensor::begin()
{
        Wire.begin();
}
#endif

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

    #ifdef ARDUINO
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
    #else
        if(!bcm2835_init())
            throw I2CError("Could not initialize bcm2835 library");
        if(!bcm2835_i2c_begin())
            throw I2CError("Could not initialize bcm2835 i2c connection.")
        bcm2835_i2c_setSlaveAddress(static_cast<uint8_t> address);
        char type_write = static_cast<char>(type);
        bcm2835_i2c_write(&type_write, 1);
        char buffer[6];
        bcm2835_i2c_read_register_rs(&type_write, buffer, 3);
        float temp = (((buffer[1] << 8) + buffer[0]) * 0.02) - 0.01;
        if (scale != Scale::KELVIN)
            temp -= 273.15;
        if (scale == Scale::FARENHEIT)
            temp = (temp * 9 / 5) + 32;
    #endif

    return temp;
}

}