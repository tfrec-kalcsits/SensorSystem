#include <hub/internet/helperfunctions.h>
#include <curl/curl.h>
#include <cstdlib>

namespace sensorsystem
{

bool curlConnectionTest(sv::string_view test_url)
{
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, test_url.data());
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_perform(curl);
    long response;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
    curl_easy_cleanup(curl);
    return response == 200;
}

bool ifconfigConnectWifi()
{
    //note: this is only tested and working on Raspberry Pi
    //note: system() calls are known to be unsecure
    return system("ifconfig wlan0 up") == 0;
}

bool ifconfigDisconnectWifi()
{
    //note: this is only tested and working on Raspberry Pi
    //note: system() calls are known to be unsecure
    return system("ifconfig wlan0 down") == 0;
}

}