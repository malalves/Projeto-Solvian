#include <SoftwareSerial.h>

SoftwareSerial 2aSerial(2,3);

void setup()
{
  2aSerial.begin(19200);
  Serial.begin(19200);
}

void loop()
{
  if (2aSerial.available())
    Serial.write(netSerial.read());
  if (Serial.available())
    2aSerial.write(Serial.read());
}

/*
	ainda precisamos definir onde vamos colocar os sensores
	para definir quais informações vamos transferir pela via serial
*/