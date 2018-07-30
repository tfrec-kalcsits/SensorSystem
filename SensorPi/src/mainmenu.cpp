#include <sensorpi/mainmenu.h>
#include <sensorpi/ui.h>
#include <packet.h>
#include <cstring>

namespace sensorsystem
{

enum Option {LOG, UPLOAD, CONNECT, DISCONNECT, RETURN };

static Packet optionToPacket(Option option, float ambient, float object, float lux, const std::string& signature)
{
    Packet::Flag flag;
    switch(option)
    {
        case LOG: flag = Packet::Flag::LOG;
            break;
        case UPLOAD: flag = Packet::Flag::UPLOAD;
            break;
        case CONNECT: flag = Packet::Flag::CONNECT;
            break;
        case DISCONNECT: flag = Packet::Flag::DISCONNECT;
            break;
        default;
            break;
    }

    Packet packet;
    packet.flag = flag;
    packet.ambient_temperature = ambient;
    packet.object_temperature = object;
    packet.lux = lux;
    strncpy(packet.signature, signature.c_str(), 10);
    return packet;
}

static void printOption(int lcd, Option option)
{
    lcdClear(lcd_handle);
    lcdHome(lcd_handle);
    switch(option)
    {
        case LOG: lcdPuts(lcd, "    < LOG >");
            break;
        case UPLOAD: lcdPuts(lcd, "  < UPLOAD >");
            break;
        case CONNECT: lcdPuts(lcd, "  < CONNECT >");
            break;
        case DISCONNECT: lcdPuts(lcd, " < DISCONNECT >");
            break;
        case SIGNATURE: lcdPuts(lcd, " < SIGNATURE >");
            break;
        case RETURN: lcdPuts(lcd, "  < RETURN >");
    }
}

void runMainMenu(int lcd_handle, RadioTransmitter& radio, float ambient, float object, float lux, const std::string& signature);
{
    lcdClear(lcd_handle);
    lcdHome(lcd_handle);
    lcdPuts(lcd_handle, "   MAIN MENU");
    wairForRelease(lcd_handle);
    lcdClear(lcd_handle);
    lcdHome(lcd_handle);

    Option option = LOG;
    printOption(lcd_handle, option);

    for(;;)
    {
        uint8_t button = waitForInput(lcd_handle);
        if(button == AF_LEFT)
        {
            option = option == LOG ? RETURN : option - 1;
            printOption(lcd_handle, option);
        }
        else if(button == AF_RIGHT)
        {
            option = option == RETURN ? LOG : option + 1;
            printOption(lcd_handle, option);
        }
        else if(button & BUTTON_SELECT)
        {
            break;
        }
    }

    switch(option)
    {
        case RETURN:
            break;
        default: radio.sendPacket(optionToPacket(option, ambient, object, lux, signature));
    }
}

}