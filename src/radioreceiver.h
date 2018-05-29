#ifndef SENSORNETWORK_RADIORECEIVER_H
#define SENSORNETWORK_RADIORECEIVER_H

#include "packet.h"

/**
 * @brief This header file contains the abstract RadioReceiver interface for the Networking module.
 * 
 * @file radioreceiver.h
 * @author Ryan Mullin
 * @date 2018-05-21
 */

namespace sensornetwork
{

///The abstract interface for a receiving radio in the sensor system.
class RadioReceiver
{
    public:
    ///Checks if a packet is available to get.
    ///Always call before getPacket().
    virtual bool isPacketAvailable() = 0;
    /**
     * Gets the next packet available for reading.
     * Always use isPacketAvailable() before calling.
     * 
     * @return The packet read from the radio. 
     */
    virtual Packet getPacket() = 0;
    virtual ~RadioReceiver() = default;

};

}

#endif