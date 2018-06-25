/**
 * @brief 
 * 
 * @file tempsensor.h
 * @author Ryan Mullin
 * @date 2018-05-22
 */

#ifndef SENSORSYSTEM_SENSOR_TEMPSENSOR_H
#define SENSORSYSTEM_SENSOR_TEMPSENSOR_H

namespace sensorsystem
{

class TempSensor
{
    public:
    enum class Scale { CELSIUS, KELVIN, FARENHEIT };
    virtual float getAmbientTemperature() = 0;
    virtual float getObjectTemperature() = 0;
    void setScale(Scale scale);
    
    virtual ~TempSensor() = default;

    protected:
    Scale scale;
};

}

#endif