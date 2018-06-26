#ifndef ARDUINO
#ifndef SENSORSYSTEM_SENSOR_CORE_I2CERROR_H
#define SENSORSYSTEM_SENSOR_CORE_I2CERROR_H

#include <stdexcept>
#include <string>

namespace sensorsystem
{

class I2CError : public std::runtime_error
{
    public:
    I2CError(const std::string& what);
};

}

#endif
#endif