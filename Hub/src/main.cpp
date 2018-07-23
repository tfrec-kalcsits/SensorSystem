#include <memory>
#include <future>
#include <fstream>
#include <string>
#include <queue>
#include <iostream>

#include <radioreceiver.h>
#include <rf24radioreceiver.h>
#include <byte.h>

#include <hub/internet/internetdevice.h>
#include <hub/storage/filestorage.h>
#include <hub/storage/remotestorage.h>
#include <hub/config.h>
#include <hub/cursesui.h>
#include <hub/compatibility.h>

using namespace sensorsystem;
using std::unique_ptr;
using std::async;
using std::ifstream;
using std::ofstream;
using std::string;
using std::future;
using std::launch;
using std::move;
using std::queue;
using std::cin;


int main()
{
    struct request
    {
        enum Type {LOG, UPLOAD, CONNECT, TEST, DISCONNECT};
        Type type;
        opt::optional<Measurement> measurement;
    };
    
    CursesUI ui;
    
    if(!fs::exists("/etc/sensorsystem-hub.ini"))
    {
        ui.write("No config file found. File should be located at /etc/sensorsystem.ini");  
        return 1;
    }

    queue<request> request_queue;

    //load config file
    ifstream config_file("/etc/sensorsystem-hub.ini");
    Config config(config_file);
    config_file.close();

    //load drivers
    auto radio = config.getRadio();
    auto filestorage = config.getFileStorage();
    auto remotestorage = config.getRemoteStorage();
    auto internet = config.getInternetDevice();

    future<bool> bool_result;
    bool processing = false;
    while(true)
    {
        //check for user input
        if(auto input = ui.read())
        {
            if(*input == "quit")
            {
                ui.write("shutting down...");
                break;    
            }

            else if(*input == "upload")
            {
                ui.write("starting upload\n");
                request_queue.push({request::UPLOAD, {}});
            }

            else if(*input == "connect")
            {
                ui.write("starting connection\n");
                request_queue.push({request::CONNECT, {}});
            }

            else if(*input == "test")
            {
                ui.write("starting test\n");
                request_queue.push({request::TEST, {}});
            }

            else if(*input == "disconnect")
            {
                ui.write("disconnecting\n");
                request_queue.push({request::DISCONNECT, {}});
            }

            else
            {
                ui.write("command " + *input + " not recognized\n");
            }
        }

        if(radio->isPacketAvailable())
        {
            ui.write("Received request from radio\n");
            auto packet = radio->getPacket();
            switch(packet.flag)
            {
                case Packet::Flag::CONNECT: request_queue.push({request::LOG, {}});
                    break;
                case Packet::Flag::DISCONNECT: request_queue.push({request::DISCONNECT, {}});
                    break;
                case Packet::Flag::TEST: request_queue.push({request::TEST, {}});
                    break;
                case Packet::Flag::UPLOAD: request_queue.push({request::UPLOAD, {}});
                    break;
                case Packet::Flag::LOG: 
                    Measurement measurement = {packet.ambient_temperature,
                        packet.object_temperature, packet.lux, string(packet.signature), getTimestamp()};
                    request_queue.push({request::LOG, measurement});
                    break;
            }
        }

        if(processing)
        {
		ui.write("processing request\n");
            if(bool_result.valid())
            {
				ui.write("process finished\n");
                string type;
                switch(request_queue.front().type)
                {
                    case request::CONNECT: type = "connect";
                        break;
                    case request::UPLOAD: type = "upload";
                        break;
                    case request::TEST: type = "request";
                        break;
                    case request::DISCONNECT: type = "disconnect";
                        break;
                    case request::LOG: type = "log";
                }
                processing = false;
                request_queue.pop();
                ui.write(type + " request " + (bool_result.get() ? "success\n" : "false\n"));
            }
        }

        if(!processing && !request_queue.empty())
        {
            processing = true;
            switch(request_queue.front().type)
            {
                case request::CONNECT: bool_result = move(async([&](){return internet->connect();}));
                    break;
                case request::LOG: bool_result = move(async([&](){return filestorage->recordMeasurementToFile(request_queue.front().measurement.value());}));
                    break;
                case request::UPLOAD: bool_result = move(async([&](){return remotestorage->syncFiles();}));
                    break;
                case request::TEST: bool_result = move(async([&](){return internet->test();}));
                    break;
                case request::DISCONNECT: bool_result = move(async([&](){return internet->disconnect();}));
            }
        }
    }

    return 0;
}
