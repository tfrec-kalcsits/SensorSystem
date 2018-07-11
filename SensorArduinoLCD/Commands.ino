void log() {
  float ambient = temp_sensor.getAmbientTemperature();
  float object = temp_sensor.getObjectTemperature();
  float lux = light_sensor.getLux();
  Packet packet = defaultPacket(Packet::Flag::LOG);
  packet.ambient_temperature = ambient;
  packet.object_temperature = object;
  packet.lux = lux;
  for(int i = 0; i < 10; i++)
    packet.signature[i] = signature[i];
  lcd.clear();
  lcd.setCursor(0,0);
  if(radio->sendPacket(packet))
    lcd.print("REQUEST\nSUCCESSFUL");
  else
    lcd.print("REQUEST\nFAILED");
}

void test() {
  lcd.clear();
  lcd.setCursor(0,0);
  if(radio->sendPacket(defaultPacket(Packet::Flag::TEST)))
    lcd.print("REQUEST\nSUCCESSFUL");
  else
    lcd.print("REQUEST\nFAILED");
}

void upload() {
  lcd.clear();
  lcd.setCursor(0,0);
  if(radio->sendPacket(defaultPacket(Packet::Flag::UPLOAD)))
    lcd.print("REQUEST\nSUCCESSFUL");
  else
    lcd.print("REQUEST\nFAILED");
}

void connect() {
  lcd.clear();
  lcd.setCursor(0,0);
  if(radio->sendPacket(defaultPacket(Packet::Flag::CONNECT)))
    lcd.print("REQUEST\nSUCCESSFUL");
  else
    lcd.print("REQUEST\nFAILED");
}

void disconnect() {
  lcd.clear();
  lcd.setCursor(0,0);
  if(radio->sendPacket(defaultPacket(Packet::Flag::DISCONNECT)))
    lcd.print("REQUEST\nSUCCESSFUL");
  else
    lcd.print("REQUEST\nFAILED");
}

void resetSignature() {
  //TODO
}

Packet defaultPacket(Packet::Flag flag) {
  Packet packet;
  packet.flag = flag;
  return packet;
}

