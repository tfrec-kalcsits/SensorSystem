#include <radioreceiver.h>
#include <radiotransmitter.h>
#include <rf24radioreceiver.h>
#include <rf24radiotransmitter.h>

using namespace sensornetwork;

RadioTransmitter * transmitter;
int ambient;

void setup() {
  // put your setup code here, to run once:
  transmitter = new RF24RadioTransmitter(9, 10, {"1Node"});
  ambient = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  Packet temp;
  temp.ambient_temperature = ambient++;
  transmitter->sendPacket(temp);
  delay(3000);
}
