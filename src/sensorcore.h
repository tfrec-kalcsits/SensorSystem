#ifndef SENSORSYSTEM_SENSOR_CORE_SENSORCORE_H
#define SENSORSYSTEM_SENSOR_CORE_SENSORCORE_H

#include <packet.h>
#include <radioreceiver.h>

#include "tempsensor.h"
#include "lightsensor.h"

namespace sensorsystem
{

class SensorCore
{
    public:
    SensorCore(TempSensor *t, LightSensor *l, RadioTransmitter *r, char *signature="no sig");
    bool makeRequest(Packet::Flag flag)

    private:
    TempSensor *temp_sensor;
    LightSensor *light_sensor;
    RadioTransmitter *radio;
    char[10] signature;
};

}
#endif