#pragma once

#include <string_view>
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