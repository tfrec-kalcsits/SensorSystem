#pragma once

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

tm getTimestamp();

}
