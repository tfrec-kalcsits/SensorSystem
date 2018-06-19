#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <exception>

#include <sensorsystem-networking/RadioReceiver.h>
#include <sensorsystem-networking/RF24RadioReceiver.h>

#include <hub/storage/filestorage.h>
#include <hub/storage/remotestorage.h>
#include <hub/internet/internetdevice.h>


namespace sensorsystem
{

class NoSectionError : public std::runtime_error
{
    NoSectionError(const string& what);
}

class Config
{
    public:
    Config(std::ifstream& infile);
    std::unique_ptr<RadioReceiver> getRadio();
    std::unique_ptr<RemoteStorage> getRemoteStorage();
    std::unique_ptr<FileStorage> getLocalStorage();
    std::unique_ptr<InternetDevice> getInternetDevice();

    private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> map;
};

}