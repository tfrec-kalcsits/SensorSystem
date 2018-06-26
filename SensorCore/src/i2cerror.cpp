#ifndef ARDUINO
#include "i2cerror.h"

namespace sensorsystem
{

I2CError::I2CError(const std::string& what) : std::runtime_error(what){}

}

#endif