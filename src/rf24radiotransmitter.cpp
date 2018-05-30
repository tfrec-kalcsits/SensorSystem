#include "rf24radiotransmitter.h"
#include "packet.h"

namespace sensornetwork
{

RF24RadioTransmitter::RF24RadioTransmitter(uint16_t gpio, uint16_t ce, byte pipe[])
    : radio(gpio, ce)
{
    radio.begin();
    radio.setAutoAck(true);
    radio.enableAckPayload();
    radio.setRetries(15,15);
    radio.openWritingPipe(pipe);
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
}

bool RF24RadioTransmitter::sendPacket(const Packet& packet)
{
    if(!radio.write(&packet, sizeof(Packet)))
        return false;
    else
    {
        if(!radio.available())
            return false;
        else
        {
            bool total = false;
            while(radio.isAckPayloadAvailable()
            {
                bool ack;
                radio.read(&ack, sizeof(bool));
                total |= ack;
            }
            return total;
        }
    }
}

}