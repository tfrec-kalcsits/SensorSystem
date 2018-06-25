#pragma once

#include <queue>
#include <mutex>
#include <sensorsystem-networking/packet.h>
#include <hub/compatibility.h>

namespace sensorsystem
{

class PacketQueue
{
    public:
    void enqueue(const Packet& packet);
    opt::optional<Packet> dequeue();

    private:
    std::queue queue_;
    std::mutex lock;
}

}