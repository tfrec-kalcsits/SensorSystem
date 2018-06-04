#include "tslsensor.h"

namespace sensorsystem
{

TSLSensor::TSLSensor(uint8_t address) : sensor(address, 12345)
{
    sensor.enableAutoRange(true);
};

bool TSLSensor::begin()
{
    sensor.begin();
}

float TSLSensor::getLux()
{
    sensors_event_t event;
    sensor.getEvent(&event);
    return event.light;
}

}