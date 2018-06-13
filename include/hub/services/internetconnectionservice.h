#pragma once

#include <memory>
#include <hub/internet/internetdevice.h>

namespace sensorsystem
{

class InternetConnectionService
{
    public:
    InternetConnectionService(std::unique_ptr<InternetDevice> device);
    bool testConnection();
    bool connect();
    bool disconnect();

    private:
    std::unique_ptr<InternetDevice> device;
};

}