#pragma once

#include <optional>

#include <sensorsystem-networking/radioreceiver.h>
#include <sensorsystem-networking/rf24radioreceiver.h>

namespace sensorsystem
{

class RadioController
{
    public:
    RadioController(std::unique_ptr<RadioReceiver> radio, std::unique_ptr<);
    std::optional<Packet> pollPackets();
};

}