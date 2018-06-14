#include <memory>
#include <thread>
#include <atomic>
#include <sensorsystem-networking/radioreceiver.h>
#include <sensorsystem-networking/rf24radioreceiver.h>



void radioProc(std::atomic_bool& end, std::unique_ptr)
{

}

int main()
{
    std::unique_ptr<RadioReceiver> radio;
    std::atomic_bool end;

    return 0;
}