/**
 * @brief This file defines the RF24RadioTransmitter,
 * the RF24 Driver/Adapter for the library.
 * 
 * @file rf24radiotransmitter.h
 * @author Ryan Mullin
 * @date 2018-05-22
 */

#ifndef SENSORNETWORK_RF24RADIOTRANSMITTER_H
#define SENSORNETWORK_RF24RADIOTRANSMITTER_H

#include "../thirdparty/RF24/RF24.h"

#ifndef ARDUINO
    #include "byte.h"
#endif

#include <RF24.h>

namespace sensornetwork
{

class RF24RadioTransmitter : public RadioTransmitter
{
    public:
    RF24RadioTransmitter(uint16_t gpio, uint16_t ce, byte pipe[]);
    bool sendPacket(const Packet& packet);

    private:
    RF24 radio;
};

}

#endif