#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <exception>

namespace sensorsystem
{

class NoSectionError : std::runtime_error
{
    NoSectionError(const std::string& what);
}

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> getConfig(std::ifstream& infile);

}