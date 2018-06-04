#include "tslsensor.h"

TSLSensor::TSLSensor(Address address) : sensor(static_cast<uint8_t>(address), 1)
{
    sensor.begin();
    sensor.enableAutoRange(true);
    sensor.setIntegrationTime(TSL_INTEGRATIONTIME_13MS);
}

uint32_t TSLSensor::getLux()
{
    uint16_t broadband, ir;
    sensor.getLuminosity(&broadband, &ir);
    return sensor.calculateLux(broadband, ir);
}