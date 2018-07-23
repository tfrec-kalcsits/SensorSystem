#include <string>
#include <hub/storage/dropboxstorage.h>

using namespace sensorsystem;

int main(int argc, char* argv[])
{
    std::string token = argv[1];
    std::string prefix_path = "./";
    DropboxStorage storage(token, prefix_path);
    storage.syncFiles();
    return 0;
}
