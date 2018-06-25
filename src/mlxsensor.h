/**
 * @brief 
 * 
 * @file mlxsensor.h
 * @author Ryan Mullin
 * @date 2018-05-23
 */

#ifndef SENSORSYSTEM_SENSOR_MLXSENSOR_H
#define SENSORSYSTEM_SENSOR_MLXSENSOR_H

#include "tempsensor.h"
#include <stdint.h>


namespace sensorsystem
{

class MLXSensor : public TempSensor
{
    public:
    static const uint8_t default_address = 0x5A;

    MLXSensor(uint8_t address = default_address);
    void begin();
    float getAmbientTemperature();
    float getObjectTemperature();

    private:
    enum class Temperature {AMBIENT = 0x06, OBJECT = 0x07};
    float readTemperature(Temperature type);
    uint8_t address;
};

}

#endif