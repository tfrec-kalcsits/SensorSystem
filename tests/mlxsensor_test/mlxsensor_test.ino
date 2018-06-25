#include <tempsensor.h>
#include <mlxsensor.h>

using namespace sensorsystem;

MLXSensor mlx;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mlx.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("====================================");
  Serial.print("AMBIENT: ");
  Serial.println(mlx.getAmbientTemperature());
  Serial.print("OBJECT: ");
  Serial.println(mlx.getObjectTemperature());
  delay(1000);
}
