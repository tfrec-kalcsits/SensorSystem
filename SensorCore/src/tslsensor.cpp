#include "tslsensor.h"
#ifndef ARDUINO
	extern "C" {
    #include <tsl2561.h>
	}
    #include "i2cerror.h"
#endif

namespace sensorsystem
{

TSLSensor::TSLSensor(uint8_t address)
#ifdef ARDUINO 
    : sensor(address, 12345)
#else
	: address(address)
#endif
{
    #ifdef ARDUINO
        sensor.enableAutoRange(true);
    #endif
}

bool TSLSensor::begin()
{
    #ifdef ARDUINO
        sensor.begin();
	return true;
    #else
        tsl = tsl2561_init(address, "/dev/i2c-1");
        tsl2561_enable_autogain(tsl);
        tsl2561_set_integration_time(tsl, TSL2561_INTEGRATION_TIME_13MS);
	return tsl != nullptr;
    #endif
}

float TSLSensor::getLux()
{
    #ifdef ARDUINO
        sensors_event_t event;
        sensor.getEvent(&event);
        return event.light;
    #else
	//hacky workaround for issues using tsl2561 and mlx90614 at the
	//same time. Future versions should fix this
	float lux = 0.0f;
	while(lux == 0.0f)
            lux = tsl2561_lux(tsl);
	return lux;
    #endif
}

}
