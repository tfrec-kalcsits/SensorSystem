#pragma once

#include <vector>
#include <hub/compatibility.h>
#include "remotestorage.h"

namespace sensorsystem
{

class DropboxStorage : public RemoteStorage
{
    public:
    DropboxStorage(std::string oauth_access_token, std::string prefix_path);
    bool syncFiles() override;

    private:
    std::string oauth_access_token;
    std::string prefix_path;
};

std::vector<char> readFileBinary(sv::string_view path);

}
