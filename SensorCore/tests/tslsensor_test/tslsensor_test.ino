//A test driver for the TSLSensor for Arduino platforms

#include <tslsensor.h>

using namespace sensorsystem;

TSLSensor sensor;

void setup()
{
    Serial.begin(9600);
    Serial.println("test");
    sensor.begin();
}

void loop()
{
    Serial.println("===================================");
    Serial.print("LUX: ");
    Serial.println(sensor.getLux());
    delay(3000);
}