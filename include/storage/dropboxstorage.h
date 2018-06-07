#ifndef SENSORSYSTEM_HUB_STORAGE_DROPBOXSTORAGE_H
#define SENSORSYSTEM_HUB_STORAGE_DROPBOXSTORAGE_H

#include <string>

#include <core/interfaces/remotestorage.h>

namespace sensorsystem
{

class DropboxStorage : public RemoteStorage
{
    public:
    DropboxStorage(std::string oauth_access_token, int max_file_size=150);
    bool uploadFile(const std::string &path);

    private:
    std::string oauth_access_token;
    std::string dropbox_folder;

    static const std::string upload_url = "https://content.dropboxapi.com/2/files/upload";
};

}

#endif