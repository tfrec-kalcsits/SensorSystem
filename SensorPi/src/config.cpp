#include <SensorPi/config.h>
#include <rf24radioreceiver.h>
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

std::unique_ptr<RadioReceiver> Config::getRadio()
{
	std::string type = map["radio"]["type"];
	if (type == "RF24")
	{
		uint16_t ce = stoi(map["radio"]["ce"]);
		uint16_t csn = stoi(map["radio"]["csn"]);
		int num_pipes = 0;
		byte pipe[6][6];
		std::string buffer;
		std::istringstream pipestream(map["radio"]["pipes"]);
		while (getline(pipestream, buffer, ','))
		{
			strncpy((char*)pipe[num_pipes], buffer.data(), 6);
			num_pipes++;
		}
		return std::unique_ptr<RadioReceiver>(new RF24RadioReceiver(ce, csn, pipe, num_pipes));
	}
	return nullptr;
}

std::unique_ptr<TempSensor> Config::getTempSensor()
{
	std::string type = map["tempsensor"]["type"];
	if (type == "MLX90614")
	{
		int address = std::stoi(map["tempsensor"]["address"]);
		return std::unique_ptr<TempSensor>(new MLXSensor(address));
	}
}

std::string Config::getSignature()
{
	return map["signature"]["signature"];
}

}
