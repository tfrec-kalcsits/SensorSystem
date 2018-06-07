#ifndef SENSORSYSTEM_HUB_CORE_DATA_MEASUREMENT_H
#define SENSORSYSTEM_HUB_CORE_DATA_MEASUREMENT_H

#include <string>
#include <ctime>

namespace sensorsystem
{

struct Measurement
{
    float ambient, object, lux;
    std::string signature;
    tm timestamp;
};

}

#endif