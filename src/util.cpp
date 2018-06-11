#include <sstream>
#include <hub/util.h>

namespace sensorsystem
{

std::string tmToString(const tm& time, char separator='-')
{
    std::ostringstream format;
    format << time.tm_mon + 1 << separator << time.tm_mday << separator << time.tm_year + 1900;
    return format.str();
}

}