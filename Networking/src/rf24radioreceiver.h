#ifndef SENSORSYSTEM_RF24RADIORECEIVER_H
#define SENSORSYSTEM_RF24RADIORECEIVER_H

#include "radioreceiver.h"


#include <RF24.h>
#ifndef ARDUINO
	#include "byte.h"
#endif


/**
 * @brief Contains the driver class for the RF24 radio receiver.
 * 
 * @file rf24radioreceiver.h
 * @author Ryan Mullin
 * @date 2018-05-21
 */

namespace sensorsystem
{

/**
 * @class RF24RadioReceiver rf24radioreceiver.h
 * @extends RadioReceiver
 * @brief A driver class for using the RadioReceiver interface with an nrf24l01+ radio.
 */
class RF24RadioReceiver : public RadioReceiver
{
    public:
    RF24RadioReceiver(uint16_t ce, uint16_t csn, byte pipes[][6], int num_pipes);
    bool isPacketAvailable();
    Packet getPacket();

    private:
    RF24 radio;
    byte last_pipe;
};

}

#endif
