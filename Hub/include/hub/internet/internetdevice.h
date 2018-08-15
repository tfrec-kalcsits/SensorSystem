#pragma once

namespace sensorsystem
{

class InternetDevice
{
    public:
    virtual bool connect() = 0;
    virtual bool test() = 0;
    virtual bool disconnect() = 0;
};

}
