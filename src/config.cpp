#include <regex>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <hub/config.h>

namespace sensorsystem
{

NoSectionError::NoSectionError(const string& what) : std::runtime_error(what){}

Config::Config(std::ifstream& infile)
{
    std::string header = "";
    std::regex header_match(R"^[\w+]$"), value_match(R"^\w+=\w+?");
    while(getline(infile, buffer))
    {
    if(regex_match(buffer, header_match))
        header = buffer.substr(1, buffer.size() - 1);
    else if(regex_match(buffer, value_match))
    {
        if(header == "")
            throw NoSectionError("No Sections values in config file");
            auto split_pos = buffer.find("=");
            std::string name = buffer.substr(0, split_pos), value = buffer.substr(split_pos + 1, buffer.size());
            map[header][name] = value;
        }
    }
}

std::unique_ptr<RadioReceiver> Config::getRadio()
{
    std::string type = config['radio']['type'];
    if(type == "RF24")
    {
        uint16_t ce = stoi(config['radio']['ce']);
        uint16_t csn = stoi(config['radio']['csn']);
        int num_pipes = 0;
        byte pipe[6][6]
        std::string buffer;
        std::istringstream pipestream(config['radio']['pipes']);
        while(getline(pipestream, buffer, ","))
        {
            strncpy((char*)pipe[num_pipes], buffer.data(), 6);
            num_pipes++;
        }
        return make_unique<RF24RadioReceiver>(ce, csn, pipe, num_pipes);
    }
    return nullptr;
}

std::unique_ptr<RemoteStorage> Config::getRemoteStorage()
{
    std::string type = config['remotestorage']['type'];
    if(type == "Dropbox")
    {
        std::string oauth = config['remotestorage']['oauth'];
        std::string localpath = config['filestorage']['path'];
        std::string remotepath = config['remotestorage']['path'];
        return make_unique<DropboxStorage>(oauth, remotepath, localpath);
    }
    return nullptr;
}

std::unique_ptr<FileStorage> Config::getLocalStorage()
{
    std::string type = config['filestorage']['type'];
    if(type == "CSV")
    {
        std::string path = config['filestorage']['path'];
        return make_unique<CSVFileStorage>(path);
    }
    return nullptr;
}

std::unique_ptr<InternetDevice> getInternetDevice()
{
    std::string type = config['internet']['type'];
    if(type == "wifi")
    {
        std::string test_address = config['internet']['testaddress'];
        if(test_address == "")
            test_address = "8.8.8.8";
        return make_unique<WifiInternetDevice>(test_address);
    }
    return nullptr;
}

}