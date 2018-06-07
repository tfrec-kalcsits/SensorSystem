#include <cstdio>

#include <curl/curl.h>

#include <core/util.h>

namespace sensorsystem
{

DropboxStorage::DropboxStorage(std::string oauth_access_token, std::string dropbox_folder)
    : oauth_access_token(oauth_access_token), dropbox_foler(dropbox_folder)
{}

bool DropboxStorage::uploadFile(const std::string &path)
{
    FILE *fp = fopen(path.c_string(), "rb");
    if(!fp)
        return false;

    size_t file_size = getFileSize(path);
    CURL *curl = curl_easy_init();
}

}