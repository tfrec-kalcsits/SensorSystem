//this is the receiver portion of the arduino test sketch for the SensorSystem-Networking library

#include <radioreceiver.h>
#include <radiotransmitter.h>
#include <rf24radioreceiver.h>
#include <rf24radiotransmitter.h>

using namespace sensornetwork;

byte pipes[1][6] = {"1NODE"};
RadioReceiver * receiver;

void setup() {
  receiver = new RF24RadioReceiver(9, 10, pipes, 1);
  Serial.begin(9600);  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(receiver->isPacketAvailable())
  {
    Packet temp = receiver->getPacket();
    Serial.println("RECEIVED PACKET");
    Serial.print("Ambient Temperature: ");
    Serial.println(temp.ambient_temperature);
    Serial.println("=======================");
  }

}
