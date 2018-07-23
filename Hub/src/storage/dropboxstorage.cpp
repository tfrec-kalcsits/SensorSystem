#include <fstream>
#include <curl/curl.h>
#include <hub/storage/dropboxstorage.h>

namespace sensorsystem
{

DropboxStorage::DropboxStorage(std::string oauth_access_token, std::string prefix_path)
    : oauth_access_token(oauth_access_token), prefix_path(prefix_path){}

bool DropboxStorage::syncFiles()
{
    std::vector<std::string> unsynced_files;
    std::string buffer;
    std::fstream sync_file(prefix_path + ".sync", std::ios::in);
    while(getline(sync_file, buffer))
        unsynced_files.push_back(std::move(buffer));
    sync_file.close();
    sync_file.open(prefix_path, std::ios::out);

    bool fail = false;
    for(auto& file : unsynced_files)
    {
        if(!fail)
        {
			curl_slist* header = nullptr;
            header = curl_slist_append(header, std::string("Authorization: Bearer " + oauth_access_token).c_str());
            header = curl_slist_append(header, std::string("Dropbox-API-Arg: {\"path\": \"/" + file + "\",\"mode\": \"overwrite\",\"autorename\": true,\"mute\": false}").c_str());
            header = curl_slist_append(header, "Content-Type: application/octet-stream");

            std::vector<char> raw_data = readFileBinary(file);

            CURL* curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_URL, "https://content.dropboxapi.com/2/files/upload");
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
            curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, raw_data.data());
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.52.1");

            fail = (curl_easy_perform(curl) != CURLE_OK);
            
            curl_easy_cleanup(curl);
            curl_slist_free_all(header);
        }

        if(fail)
        {
            sync_file << file << std::endl;
        }
    }

    return !fail;
}

std::vector<char> readFileBinary(sv::string_view path)
{
    std::ifstream file(std::string(path), std::ios::binary | std::ios::ate);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    file.read(buffer.data(), size);
    return buffer;
}

}
