//A test driver for the TSLSensor for Arduino platforms

#include <tslsensor.h>

TSLSensor sensor;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println("===================================");
    Serial.print("LUX: ");
    Serial.println(sensor.getLux();
    delay(3000);
}