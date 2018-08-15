#include <hub/internet/pppinternetdevice.h>
#include <hub/internet/helperfunctions.h>
#include <cstdlib>

namespace sensorsystem
{

PPPInternetDevice::PPPInternetDevice(std::string peer, std::string test_url)
	: connect_command("pon " + peer),
	  disconnect_command("poff " + peer),
   	  test_url(std::move(test_url))
	{}

bool PPPInternetDevice::connect()
{
	return system(connect_command.c_str()) != -1;
}

bool PPPInternetDevice::disconnect()
{
	return system(disconnect_command.c_str()) != -1;
}

bool PPPInternetDevice::test()
{
	return curlConnectionTest(test_url);
}

}
