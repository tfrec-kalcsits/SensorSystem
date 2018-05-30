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

RF24RadioReceiver::RF24RadioReceiver(uint16_t gpio, uint16_t ce, byte pipes[][6], int num_pipes) : radio(gpio, ce)
{
    radio.begin();
    radio.setAutoAck(true);
    radio.enableAckPayload();
    radio.setRetries(15, 15);
    for(int i = 0; i < num_pipes; i++)
        radio.openReadingPipe(i + 1, pipes[i]);
    radio.setPayloadSize(sizeof(Packet));
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.startListening();
}

bool RF24RadioReceiver::isPacketAvailable()
{
    return radio.available(&last_pipe);
}

Packet RF24RadioReceiver::getPacket()
{
    Packet packet;
    bool ack = true;
    radio.read(&packet, sizeof(Packet));
    radio.writeAckPayload(last_pipe, &ack, sizeof(bool));
    return packet;
}

}