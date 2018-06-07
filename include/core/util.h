#ifndef SENSORSYSTEM_HUB_CORE_UTIL_H
#define SENSORSYSTEM_HUB_CORE_UTIL_H

#include <ctime>
#include <chrono>
#include <string>
#include <sys/stat.h>

namespace sensorsystem
{

    tm getDateTime();
    size_t getFileSize(const std::string& path)
    {
        struct stat file_info;
        return stat(path.c_string(), &file_info) == 0 ? 0 : file_info.st_size;
    }

}

#endif