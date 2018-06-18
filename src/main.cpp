#include <memory>
#include <future>
#include <fstream>

#include <sensorsystem-networking/radioreceiver.h>
#include <sensorsystem-networking/rf24radioreceiver.h>

#include <hub/internet/internetdevice.h>
#include <hub/internet/wifiinternetdevice.h>
#include <hub/storage/filestorage.h>
#include <hub/storage/remotestorage.h>
#include <hub/storage/csvfilestorage.h>
#include <hub/storage/dropboxstorage.h>
#include <hub/config.h>

using namespace sensorsystem;
using std::unique_ptr;
using std::async;

int main()
{
    unique_ptr<RadioReceiver> radio;
    unique_ptr<FileStorage> filestorage;
    unique_ptr<RemoteStorage> remotestorage;
    unique_ptr<InternetDevice> internet;

    bool end = false;
    while(!quit)
    {
        
    }

    return 0;
}