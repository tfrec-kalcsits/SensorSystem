#include <regex>
#include <cstring>

#include <sensorpi/config.h>
#include <rf24radiotransmitter.h>
#include <mlxsensor.h>
#include <tslsensor.h>

namespace sensorsystem
{

Config::Config(std::ifstream& infile)
{
	std::string header = "";
	std::regex header_match("^\\[\\w+\\]"), value_match("^\\w+=[\\w/]+");
	std::string buffer;
	while (getline(infile, buffer))
	{
		if (regex_match(buffer, header_match))
			header = buffer.substr(1, buffer.size() - 2);
		else if (regex_match(buffer, value_match))
		{
			if (header == "")
				throw NoSectionError("No Sections values in config file");
			auto split_pos = buffer.find("=");
			std::string name = buffer.substr(0, split_pos), value = buffer.substr(split_pos + 1, buffer.size());
			map[header][name] = value;
		}
	}
}

std::unique_ptr<RadioTransmitter> Config::getRadio()
{
	std::string type = map["radio"]["type"];
	if (type == "RF24")
	{
		uint16_t ce = stoi(map["radio"]["ce"]);
		uint16_t csn = stoi(map["radio"]["csn"]);
		byte pipe[6];
		strncpy((char*)pipe, map["radio"]["pipe"].c_str(), 6);
		
		return std::unique_ptr<RadioTransmitter>(new RF24RadioTransmitter(ce, csn, pipe));
	}
	return nullptr;
}

std::unique_ptr<TempSensor> Config::getTempSensor()
{
	std::string type = map["tempsensor"]["type"];
	if (type == "MLX90614")
	{
		std::string address_buf = map["lightsensor"]["address"];
		if(address_buf == "")
			return std::unique_ptr<TempSensor>(new MLXSensor());
		int address = std::stoi(address_buf);
		return std::unique_ptr<TempSensor>(new MLXSensor(address));
	}
	return nullptr;
}

std::unique_ptr<LightSensor> Config::getLightSensor()
{
	std::string type = map["lightsensor"]["type"];
	if (type == "TSL2561")
	{
		std::string address_buf = map["lightsensor"]["address"];
		if(address_buf == "")
			return std::unique_ptr<LightSensor>(new TSLSensor());
		int address = std::stoi(address_buf);
		return std::unique_ptr<LightSensor>(new TSLSensor(address));
	}
	return nullptr;
}

std::string Config::getSignature()
{
	return map["signature"]["signature"];
}

NoSectionError::NoSectionError(const std::string& what) : std::runtime_error(what){}

}
