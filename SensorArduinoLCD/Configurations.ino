//This file contains functions to load storage from the Arduino's EEPROM
//The EEPROM will contain persistent data such as saved signatures
#include <EEPROM.h>

#define EEPROM_SIGNATURE_EXISTS 0
#define EEPROM_SIGNATURE_START 1

//This function retrieves the user's saved signature from EEPROM.
//If a signature is stored, address 0 will be set to 1 (bool true)
//The signature will be stored at addresses 1-10
void loadSignature(char * destination)
{
  if(EEPROM.read(EEPROM_SIGNATURE_EXISTS))
    for(int i = 0; i < 10; i++)
      destination[i] = EEPROM.read(EEPROM_SIGNATURE_START + i);
  else
    destination[0] = '\0';
}

//This function stores the signature into EEPROM memory.
void storeSignature(char * source)
{
  EEPROM.write(EEPROM_SIGNATURE_EXISTS, true);
  for(int i = 0; i < 10; i++)
    EEPROM.write(EEPROM_SIGNATURE_START + i, source[i]);
}

