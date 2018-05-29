#ifndef SENSORNETWORK_RADIOTRANSMITTER_H
#define SENSORNETWORK_RADIOTRANSMITTER_H

#include "packet.h"

/**
 * @brief This header file contains the class RadioTransmitter
 * 
 * @file radioreceiver.h
 * @author Ryan Mullin
 * @date 2018-05-21
 */

namespace sensornetwork
{

///The abstract interface for a transmitting radio in the sensor network.
class RadioTransmitter
{
    public:
    /**
     * @brief Send a packet to the receiving radio
     * 
     * @param packet The packet to be sent.
     * @return true if the packet was sent succesfully.
     * @return false if the packet failed to send.
     */
    virtual bool sendPacket(const Packet& packet) = 0;
    virtual ~RadioTransmitter() = default;
};

}

#endif