/**
 * @brief This file defines the RF24RadioTransmitter,
 * the RF24 Driver/Adapter for the library.
 * 
 * @file rf24radiotransmitter.h
 * @author Ryan Mullin
 * @date 2018-05-22
 */

#ifndef SENSORSYSTEM_RF24RADIOTRANSMITTER_H
#define SENSORSYSTEM_RF24RADIOTRANSMITTER_H

#include <RF24.h>

#include "radiotransmitter.h"

namespace sensorsystem
{

class RF24RadioTransmitter : public RadioTransmitter
{
    public:
    RF24RadioTransmitter(uint16_t ce, uint16_t csn, byte pipe[]);
    bool sendPacket(const Packet& packet);

    private:
    RF24 radio;
};

}

#endif
