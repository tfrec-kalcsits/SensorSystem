#pragma once
#include <string>
#include "internetdevice.h"

namespace sensorsystem
{

class PPPInternetDevice : public InternetDevice
{
	public:
	PPPInternetDevice(std::string peer, std::string test_url);
	bool connect() override;
	bool disconnect() override;
	bool test() override;

	private:
	std::string connect_command, disconnect_command, test_url;
};

}
