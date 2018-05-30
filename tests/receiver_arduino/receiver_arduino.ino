//this is the receiver portion of the arduino test sketch for the SensorSystem-Networking library

#include <radioreceiver.h>
#include <radiotransmitter.h>
#include <rf24radioreceiver.h>
#include <rf24radiotransmitter.h>

using namespace sensornetwork;

byte pipes[1][6] = {"00001"};
RadioReceiver * receiver;

void setup() {
  Serial.begin(9600);
  receiver = new RF24RadioReceiver(7, 8, pipes, 1);  

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
