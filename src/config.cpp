#include <regex>
#include <hub/configreader.h>

namespace sensorsystem
{

NoSectionError::NoSectionError(const std::string& what) : std::runtime_error(what){}

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> getConfig(std::ifstream& infile)
{
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config;
    std::string header = "";
    std::regex header_match(R"^[\w+]$"), value_match(R"^\w+=\w+?");
    while(getline(infile, buffer))
    {
        if(regex_match(buffer, header_match))
            header = buffer.substr(1, buffer.size() - 1);
        else if(regex_match(buffer, value_match))
        {
            if(header == "")
                throw NoSectionError("No header values in config file");
            auto split_pos = buffer.find("=");
            std::string name = buffer.substr(0, split_pos), value = buffer.substr(split_pos + 1, buffer.size());
            config[header][name] = value;
        }
    }
    return config;
}

}