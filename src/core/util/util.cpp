#include <core/util.h>
#include <sys/stat.h>

namespace sensorsystem
{

tm getDateTime()
{
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tm date_time = *localtime(&now);
    date_time.tm_year += 1900;
    date_time.tm_mon += 1;
    return date_time;
}


}