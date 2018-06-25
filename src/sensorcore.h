#ifndef SENSORSYSTEM_SENSOR_CORE_SENSORCORE_H
#define SENSORSYSTEM_SENSOR_CORE_SENSORCORE_H

#include <packet.h>
#include <radiotransmitter.h>

#include "tempsensor.h"
#include "lightsensor.h"
#include "measurement.h"

namespace sensorsystem
{

class SensorCore
{
    public:
    SensorCore(TempSensor &t, LightSensor &l, RadioTransmitter &r, char *signature="no sig");
    bool makeRequest(Packet::Flag flag);
    void setSignature(char * signature);
    Measurement getMeasurement();

    private:
    TempSensor& temp_sensor;
    LightSensor& light_sensor;
    RadioTransmitter& radio;
    char signature[10];
};

}
#endif