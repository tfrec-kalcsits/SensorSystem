#pragma once
#include <fstream>
#include <memory>
#include <unordered_map>
#include <string>

#include <radioreceiver.h>
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
	std::unique_ptr<RadioReceiver> getRadio();
	std::unique_ptr<LightSensor> getLightSensor();
	std::unique_ptr<TempSensor> getTempSensor();
	std::string getSignature();

	private:
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> map;
};

}
