#ifndef SENSORSYSTEM_SENSOR_CORE_TSLSENSOR
#define SENSORSYSTEM_SENSOR_CORE_TSLSENSOR

#include <Adafruit_TSL2561_U.h>

#include "lightsensor.h"

class TSLSensor : public LightSensor
{
    public:
    enum class Address {BASE=0x39, GROUND=0x29, VCC=0x49};

    TSLSensor(Address address=Address::BASE);
    int32_t getLux();

    private:
    Adafruit_TSL2561_U sensor;
};


#endif