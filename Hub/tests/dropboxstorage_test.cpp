#include <string>
#include <hub/storage/dropboxstorage.h>

using namespace sensorsystem;

int main(int argc, char* argv[])
{
    std::string token = argv[1];
    std::string path = argv[2];
    std::string prefix_path = "./";
    DropboxStorage storage(token, path, prefix_path);
    storage.syncFiles();
    return 0;
}