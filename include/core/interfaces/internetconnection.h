#ifndef SENSORSYSTEM_HUB_CORE_INTERFACES_INTERNETCONNECTION_H
#define SENSORSYSTEM_HUB_CORE_INTERFACES_INTERNETCONNECTION_H

namespace sensorsystem
{

class InternetConnection
{
    public:
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool test() = 0;
    virtual ~InternetConnection() = default;
};

}

#endif