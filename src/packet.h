#ifndef SENSORSYSTEM_PACKET_H
#define SENSORSYSTEM_PACKET_H
/**
 * @brief This header file includes the definition for the Packet struct that
 * will be sent between the RadioReceivers and RadioTransmitters
 * 
 * @file packet.h
 * @author Ryan Mullin
 * @date 2018-05-21
 */

namespace sensorsystem
{

/**
 * @brief This class defines the communication protocol between
 *  the RadioReceiver and RadioTransmitter.
 */
struct Packet
{
    ///Enum used to specify the type of packet/command.
    enum class Flag { LOG, UPLOAD, TEST, CONNECT, DISCONNECT};
    
    ///The flag for the type of packet/command.
    Flag flag;
    ///Ambient and object temperatures recorded by the sensor.
    float ambient_temperature, object_temperature, lux;
    ///Each Packet will have a unique signature that will be recorded along with the measurements.
    ///This can be used for readability and to determine what the sensor was recording.
    char signature[10];
};

}

#endif