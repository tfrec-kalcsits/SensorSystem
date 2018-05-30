/**
 * @brief This file defines the functions for RF24RadioReceiver
 * 
 * @file rf24radioreceiver.cpp
 * @author Ryan Mullin
 * @date 2018-05-22
 */

#include "rf24radioreceiver.h"

namespace sensornetwork
{

RF24RadioReceiver::RF24RadioReceiver(uint16_t ce, uint16_t csn, byte pipes[][6], int num_pipes) : radio(ce, csn)
{
    radio.begin();
    radio.setRetries(15, 15);
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    for(int i = 0; i < num_pipes; i++)
        radio.openReadingPipe(i, pipes[i]);
    radio.startListening();

}

bool RF24RadioReceiver::isPacketAvailable()
{
    return radio.available();
}

Packet RF24RadioReceiver::getPacket()
{
    Packet packet;
    radio.read(&packet, sizeof(Packet));
    return packet;
}

}