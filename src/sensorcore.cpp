#include "sensorcore.h"

namespace sensorsystem
{

SensorCore::SensorCore(TempSensor &t, LightSensor &l, RadioTransmitter &r)
    : temp_sensor(t), light_sensor(l), radio(r)
{
    for(int i = 0; i < 10 && signature[i] != '\0'; i++)
        this->signature[i] = signature[i];
}

bool SensorCore::makeRequest(Packet::Flag flag)
{
    Packet packet;
    packet.flag = flag;
    if(flag == Packet::Flag::LOG)
    {
        float ambient = temp_sensor.getAmbientTemperature();
        float object = temp_sensor.getObjectTemperature();
        float lux = light_sensor.getLux();

        packet.ambient_temperature = ambient;
        packet.object_temperature = object;
        packet.lux = lux;
        for(int i = 0; i < 10; i++)
            packet.signature[i] = signature[i];
    }

    return radio->sendPacket(packet);
}

void SensorCore::setSignature(char * signature)
{
    for(int i = 0; i < 10 & signature[i] != '\0'; i++)
        this->signature[i] = signature[i];
}

}