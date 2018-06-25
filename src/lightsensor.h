/**
 * @brief 
 * 
 * @file lightsensor.h
 * @author Ryan Mullin
 * @date 2018-05-22
 */

#ifndef SENSORSYSTEM_SENSOR_LIGHTSENSOR_H
#define SENSORSYSTEM_SENSOR_LIGHTSENSOR_H

namespace sensorsystem
{

class LightSensor
{
    public:
    virtual float getLux() = 0;
};

}

#endif