#include <radioreceiver.h>
#include <radiotransmitter.h>
#include <rf24radioreceiver.h>
#include <rf24radiotransmitter.h>
using namespace sensorsystem;

RadioTransmitter * transmitter;
int ambient;
byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("============= BEGIN ===========");
  transmitter = new RF24RadioTransmitter(7, 8, address);
  ambient = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Sending packet with temperature: ");
  Serial.println(ambient);
  Packet temp;
  temp.ambient_temperature = ambient;
  if(transmitter->sendPacket(temp))
    Serial.println("Successful transmission");
  else
    Serial.println("Transmission failed");
  ambient++;
  delay(3000);
}
