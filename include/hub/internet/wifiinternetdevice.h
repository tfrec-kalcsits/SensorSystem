#pragma once

#include <string>
#include "internetdevice.h"

namespace sensorsystem
{

class WifiInternetDevice : public InternetDevice
{
    public:
    WifiInternetDevice(std::string test_address);
    bool connect() override;
    bool test() override;
    bool disconnect() override;

    private:
    std::string test_address;
};

}