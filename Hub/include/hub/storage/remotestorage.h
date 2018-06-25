#pragma once

#include <hub/compatibility.h>

namespace sensorsystem
{

class RemoteStorage
{
    public:
    virtual bool syncFiles() = 0;
    virtual ~RemoteStorage() = default;
};

}