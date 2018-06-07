#ifndef SENSORSYSTEM_CORE_INTERFACES_REMOTESTORAGE_H
#define SENSORSYSTEM_CORE_INTERFACES_REMOTESTORAGE_H

#include <string>

#include <core/data/measurement.h>

namespace sensorsystem
{

class RemoteStorage
{
    public:
    virtual bool uploadFile(std::string path) = 0;
    virtual ~RemoteStorage() = default;
};

}


#endif