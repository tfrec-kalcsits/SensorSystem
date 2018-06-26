#include "tslsensor.h"
#ifndef ARDUINO
    #include <tsl2561.h>
    #include "i2cerror.h"
#endif

namespace sensorsystem
{

TSLSensor::TSLSensor(uint8_t address)
#ifdef ARDUINO 
    : sensor(address, 12345)
#endif
{
    #ifdef ARDUINO
        sensor.enableAutoRange(true);
    #endif
};

bool TSLSensor::begin()
{
    #ifdef ARDUINO
        sensor.begin();
    #else
        tsl = tsl2561_init(address, "/dev/i2c-1");
        tsl2561_enable_autogain(tsl);
        tsl2561_set_integration_time(tsl, TSL2561_INTEGRATION_TIME_13MS);
    return tsl != nullptr;
}

float TSLSensor::getLux()
{
    #ifdef ARDUINO
        sensors_event_t event;
        sensor.getEvent(&event);
        return event.light;
    #else
        return tsl2561_lux(tsl);
    #endif
}

}