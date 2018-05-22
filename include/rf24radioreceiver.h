#ifndef SENSORNETWORK_RF24RADIORECEIVER_H
#define SENSORNETWORK_RF24RADIORECEIVER_H

#include "radioreceiver.h"
#ifndef ARDUINO
    #include <byte.h>
#endif

#include <RF24.h>

/**
 * @brief Contains the driver class for the RF24 radio receiver.
 * 
 * @file rf24radioreceiver.h
 * @author Ryan Mullin
 * @date 2018-05-21
 */

namespace sensornetwork
{

/**
 * @class RF24RadioReceiver rf24radioreceiver.h
 * @extends RadioReceiver
 * @brief A driver class for using the RadioReceiver interface with an nrf24l01+ radio.
 */
class RF24RadioReceiver : public RadioReceiver
{
    public:
    RF24RadioReceiver(uint16_t gpio, uint16_t ce, byte pipes[][6], int num_pipes);
    bool isPacketAvailable();
    Packet getPacket();

    private:
    RF24 radio;
};

}

#endif