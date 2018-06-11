#pragma once

#include <vector>
#include <hub/compatibility.h>
#include "remotestorage.h"

namespace sensorsystem
{

class DropboxStorage : public RemoteStorage
{
    public:
    DropboxStorage(std::string oauth_access_token, std::string upload_path, std::string prefix_path="~/home/.hub/");
    bool syncFiles() override;

    private:
    const std::string oauth_access_token;
    const std::string upload_path;
    const std::string prefix_path;
};

std::vector<char> readFileBinary(sv::string_view path);

}