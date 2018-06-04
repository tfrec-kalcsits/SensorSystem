/**
 * @brief 
 * 
 * @file lightsensor.h
 * @author Ryan Mullin
 * @date 2018-05-22
 */

#ifndef SENSORSYSTEM_SENSOR_LIGHTSENSOR_H
#define SENSORSYSTEM_SENSOR_LIGHTSENSOR_H

#include <stdint.h>

namespace sensorsystem
{

class LightSensor
{
    public:
    virtual int32_t getLux() = 0;
};

}

#endif