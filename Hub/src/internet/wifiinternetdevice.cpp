#include <hub/internet/wifiinternetdevice.h>
#include <hub/internet/helperfunctions.h>

namespace sensorsystem
{

WifiInternetDevice::WifiInternetDevice(std::string test_address)
    : test_address(test_address)
{}

bool WifiInternetDevice::connect()
{
    return ifconfigConnectWifi();
}

bool WifiInternetDevice::disconnect()
{
    return ifconfigDisconnectWifi();
}

bool WifiInternetDevice::test()
{
    return curlConnectionTest(test_address);
}

}