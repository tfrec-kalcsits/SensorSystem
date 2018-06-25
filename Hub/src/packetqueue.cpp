#include <hub/packetqueue.h>

namespace sensorsystem
{

void PacketQueue::enqueue(const Packet& packet)
{
    std::unique_lock<std::mutex> l(lock);
    queue_.push(packet);
}

opt::optional<Packet> PacketQueue::dequeue()
{
    std::unique_lock<std::mutex> l(lock);
    if(queue_.empty())
        return {};
    Packet packet = queue_.front();
    queue_.pop();
    return {packet};
}

}