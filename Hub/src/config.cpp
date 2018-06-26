#include <regex>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <networking/radioreceiver.h>
#include <networking/rf24radioreceiver.h>
#include <hub/internet/wifiinternetdevice.h>
#include <hub/config.h>
#include <hub/storage/dropboxstorage.h>
#include <hub/storage/csvfilestorage.h>

namespace sensorsystem
{

NoSectionError::NoSectionError(const std::string& what) : std::runtime_error(what){}

Config::Config(std::ifstream& infile)
{
    std::string header = "";
    std::regex header_match("^\\[\\w+\\]"), value_match("^\\w+=[\\w/]+");
    std::string buffer;
    while(getline(infile, buffer))
    {
		if(regex_match(buffer, header_match))
			header = buffer.substr(1, buffer.size() - 2);
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
    std::string type = map["radio"]["type"];
    if(type == "RF24")
    {
        uint16_t ce = stoi(map["radio"]["ce"]);
        uint16_t csn = stoi(map["radio"]["csn"]);
        int num_pipes = 0;
        byte pipe[6][6];
        std::string buffer;
        std::istringstream pipestream(map["radio"]["pipes"]);
        while(getline(pipestream, buffer, ','))
        {
            strncpy((char*)pipe[num_pipes], buffer.data(), 6);
            num_pipes++;
        }
        return std::unique_ptr<RadioReceiver>(new RF24RadioReceiver(ce, csn, pipe, num_pipes));
    }
    return nullptr;
}



std::unique_ptr<RemoteStorage> Config::getRemoteStorage()
{
    std::string type = map["remotestorage"]["type"];
    if(type == "Dropbox")
    {
        std::string oauth = map["remotestorage"]["oauth"];
        std::string localpath = map["filestorage"]["path"];
        std::string remotepath = map["remotestorage"]["path"];
        return std::unique_ptr<DropboxStorage>(new DropboxStorage(oauth, remotepath, localpath));
    }
    return nullptr;
}

std::unique_ptr<FileStorage> Config::getFileStorage()
{
    std::string type = map["filestorage"]["type"];
    if(type == "CSV")
    {
        std::string path = map["filestorage"]["path"];
        return std::unique_ptr<CSVFileStorage>(new CSVFileStorage(path));
    }
    return nullptr;
}

std::unique_ptr<InternetDevice> Config::getInternetDevice()
{
    std::string type = map["internet"]["type"];
    if(type == "wifi")
    {
        std::string test_address = map["internet"]["testaddress"];
        if(test_address == "")
            test_address = "8.8.8.8";
        return std::unique_ptr<InternetDevice>(new WifiInternetDevice(test_address));
    }
    return nullptr;
}


}
