#include "rf24radiotransmitter.h"
#include "packet.h"

namespace sensorsystem
{

RF24RadioTransmitter::RF24RadioTransmitter(uint16_t ce, uint16_t csn, byte pipe[])
    : radio(ce, csn)
{
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(pipe);
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();
}

bool RF24RadioTransmitter::sendPacket(const Packet& packet)
{
    return radio.write(&packet, sizeof(Packet));
}

}