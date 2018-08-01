#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <exception>

#include <radiotransmitter.h>
#include <lightsensor.h>
#include <tempsensor.h>

namespace sensorsystem
{

class NoSectionError : public std::runtime_error
{
	public:
    NoSectionError(const std::string& what);
};

class Config
{
    public:
    Config(std::ifstream& infile);
    std::unique_ptr<RadioTransmitter> getRadio();
    std::unique_ptr<LightSensor> getLightSensor();
    std::unique_ptr<TempSensor> getTempSensor();
    std::string getSignature();

    private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> map;
};

}