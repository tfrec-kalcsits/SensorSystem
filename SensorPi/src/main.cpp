#include <fstream>
#include <iostream>
#include <string>

#include <unistd.h>
#include <wiringPi.h>

#include <sensorpi/ui.h>
#include <sensorpi/config.h>
#include <sensorpi/mainmenu.h>

using namespace sensorsystem;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;

int main()
{
	wiringPiSetupSys();
	
    //initial setup
    ifstream config_file("/etc/sensorsystem-sensor.ini");
    if(!config_file.good())
    {
        cout << "No config file found at /etc/sensorsytem-sensor.ini" << endl;
        return 1;
    }

    Config config(config_file);

    auto radio = config.getRadio();
    auto light_sensor = config.getLightSensor();
    auto temp_sensor = config.getTempSensor();
    string signature = config.getSignature();

    int lcd_handle = initLCD();
    initMainScreen(lcd_handle);

    //main loop
    for(;;)
    {
        float ambient = temp_sensor->getAmbientTemperature();
        float object = temp_sensor->getObjectTemperature();
        float lux = light_sensor->getLux();
        printMainScreenMeasurements(lcd_handle, ambient, object, lux);
        if(isButtonPressed(lcd_handle, AF_SELECT))
        {
            runMainMenu(lcd_handle, *radio, ambient, object, lux, signature);
            initMainScreen(lcd_handle);
            printMainScreenMeasurements(lcd_handle, ambient, object, lux);
        }

        sleep(1);
        
    }

    return 0;
}

