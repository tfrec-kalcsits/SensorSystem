#include <fstream>
#include <memory>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <chrono>

#include <unistd.h>
#include <wiringPi.h>

#include <radiotransmitter.h>
#include <tempsensor.h>
#include <lightsensor.h>
#include <packet.h>

#include <sensorpi/lcdplate.h>
#include <sensorpi/config.h>

using namespace sensorsystem;
using std::string;

string signature = "";

enum Option : int { LOG = 0, UPLOAD, TEST, CONNECT, DISCONNECT, SIGNATURE, AUTOLOG, QUIT };

void initGPIO()
{
	wiringPiSetup();
}

string optionToString(Option option)
{
	switch(option)
	{
		case LOG: return "LOG";
		case UPLOAD: return "UPLOAD";
		case TEST: return "TEST";
		case CONNECT: return "CONNECT";
		case DISCONNECT: return "DISCONNECT";
		case SIGNATURE: return "SIGNATURE";
		case AUTOLOG: return "AUTOLOG";
		case QUIT: return "QUIT";
	}
}

Packet optionToPacket(Option option, float ambient, float object, float lux)
{
	Packet packet;
	
	switch(option)
	{
		case LOG: packet.flag = Packet::Flag::LOG;
			break;
		case UPLOAD: packet.flag = Packet::Flag::UPLOAD;
			break;
		case TEST: packet.flag = Packet::Flag::TEST;
			break;
		case CONNECT: packet.flag = Packet::Flag::CONNECT;
			break;
		case DISCONNECT: packet.flag = Packet::Flag::DISCONNECT;
	}
	
	packet.ambient_temperature = ambient;
	packet.object_temperature = object;
	packet.lux = lux;
	strncpy(packet.signature, signature.c_str(), 10);
	
	return packet;
}

void signatureMenu(LCDPlate& ui)
{
	string buffer = "";
	for(bool select = false;!select;)
	{
		ui.clear();
		ui.move(0,0);
		ui.print("Enter Signature:\n" + buffer);
		for(bool pressed = false; !pressed;)
		{
			if(pressed = ui.isButtonPressed(LCDPlate::SELECT))
				select = true;
			else if (pressed = ui.isButtonPressed(LCDPlate::LEFT))
				buffer.pop_back();
			else if(pressed = ui.isButtonPressed(LCDPlate::RIGHT))
				buffer.push_back('A');
			else if(pressed = ui.isButtonPressed(LCDPlate::UP))
			{
				if(buffer.back() == 'Z')
					buffer.back() = '1';
				else if(buffer.back() == '9')
					buffer.back() == 'A';
			}
			else if(pressed = ui.isButtonPressed(LCDPlate::DOWN))
			{
				if(buffer.back() == 'A')
					buffer.back() = '9';
				else if(buffer.back() == '1')
					buffer.back() = 'Z';
			}
		}
	}
}

string formatReadings(float ambient, float object, float lux)
{
	using std::stringstream;
	using std::setprecision;
	stringstream format;
	format << setprecision(2) << "A: " << ambient
	       << " O: " << object << "\nLUX: "
	       << lux;
	return format.str();
}

void autolog(LCDPlate& ui, RadioTransmitter& radio, TempSensor& temp_sensor, LightSensor& light_sensor)
{
	ui.clear();
	ui.move(0,0);
	ui.print("AUTOLOG\nRUNNING");
	auto interval = std::chrono::seconds(30);
	auto start = std::chrono::system_clock::now();
	while(!ui.isButtonPressed(LCDPlate::SELECT))
	{
		if(std::chrono::system_clock::now() > start + interval)
		{
			start = std::chrono::system_clock::now();
			//send the temperature recordings
			Packet packet;
			packet.ambient_temperature = temp_sensor.getAmbientTemperature();
			packet.object_temperature = temp_sensor.getObjectTemperature();
			packet.lux = light_sensor.getLux();
			strncpy(packet.signature, signature.c_str(), 10);
			packet.flag = Packet::Flag::LOG;
			ui.clear();
			ui.move(0,0);
			ui.print(radio.sendPacket(packet) ? "Packet sent" : "Packet failed\nto send");
			sleep(1);
			ui.clear();
			ui.move(0,0);
			ui.print("AUTOLOG\nRUNNING");
		}
	}
}

Option menu(LCDPlate& ui, RadioTransmitter& radio, float ambient, float object, float lux)
{
	//get the option from the user
	Option option = LOG;
	for(bool select = false;!select;)
	{
		if(select = ui.isButtonPressed(LCDPlate::SELECT))
			select = true;
		else if(ui.isButtonPressed(LCDPlate::LEFT))
			option = (Option)(option == LOG ? QUIT : (int)option - 1);
		else if(ui.isButtonPressed(LCDPlate::RIGHT))
			option = (Option)(option == QUIT ? LOG : (int)option + 1);
		ui.clear();
		ui.move(0,0);
		ui.print(string("< ") + optionToString(option) + " >");
	}
	
	//if the option requires sending a packet, generate one.
	if(option <= 4)
	{
		ui.clear();
		ui.move(0,0);
		ui.print(radio.sendPacket(optionToPacket(option, ambient, object, lux)) ? "Request sent\nsuccessfully" : "Request failed\nto send");
	}
	else if(option == SIGNATURE)
		signatureMenu(ui);
		
	return option;
}

int main()
{
	using std::ifstream;
	using std::unique_ptr;
	
	//initialize gpio connections, needs to be called because of wiringPi
	initGPIO();
	
	LCDPlate ui;
	
	//initialize configuration files
	ifstream config_file("/etc/sensorsystem-sensor.ini");
	if(!config_file.good())
		return 1;
	Config config(config_file);
	config_file.close();
	
	//load driver classes for hardware peripherals
	unique_ptr<RadioTransmitter> radio = config.getRadio();
	unique_ptr<LightSensor> light_sensor = config.getLightSensor();
	unique_ptr<TempSensor> temp_sensor = config.getTempSensor();
	signature = config.getSignature();
	
	//print hello message
	ui.print("     Hello!");
	sleep(2);
	
	//start the main screen
	for(bool quit = false; !quit;)
	{
		float ambient = temp_sensor->getAmbientTemperature();
		float object = temp_sensor->getObjectTemperature();
		float lux = light_sensor->getLux();
		
		//clear the screen
		ui.clear();
		ui.move(0,0);
		
		//proceed to menu if select is pressed
		if(ui.isButtonPressed(LCDPlate::SELECT))
		{
			Option option = menu(ui, *radio, ambient, object, lux);
			if(option == AUTOLOG)
				autolog(ui, *radio, *temp_sensor, *light_sensor);
			else if(option == QUIT)
				quit = true;
		}
		
		else
		{
			//print measurements to the screen
			ui.print(formatReadings(ambient, object, lux));
			sleep(1);
		}
	}	
}
