#include "rf24radiotransmitter.h"
#include "packet.h"

namespace sensornetwork
{

RF24RadioTransmitter::RF24RadioTransmitter(uint16_t gpio, uint16_t ce, byte pipe[])
    : radio(gpio, ce)
{
    radio.begin();
    radio.setRetries(15,15);
    radio.openWritingPipe(pipe);
    radio.setPayloadSize(sizeof(Packet));
    radio.powerDown();
    radio.setPALevel(RF24_PA_LOW);
}

bool RF24RadioTransmitter::sendPacket(const Packet& packet)
{
    radio.powerUp();
    return radio.write(&packet, sizeof(Packet));
}

}