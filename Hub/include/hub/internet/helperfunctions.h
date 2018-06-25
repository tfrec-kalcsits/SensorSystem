#pragma once

#include <hub/compatibility.h>

namespace sensorsystem
{

bool curlConnectionTest(sv::string_view test_url);

bool ifconfigConnectWifi();

bool ifconfigDisconnectWifi();

}