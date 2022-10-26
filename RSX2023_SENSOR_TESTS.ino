#include "Arduino.h"
#include "RSX2023_Sensors.h"

int PIN_SCK = 13;
int PIN_MISO = 12;
int PIN_MOSI = 11;
int PIN_CS_BME = 9;
int PIN_CS_BMP = 10;

float SEALEVELPRESSURE_HPA = 1013.25;
int delayTime = 1000;

bool debugMode = true;

void setup() 
{
  Serial.begin(9600);

  if (debugMode)
    Serial.println("---- RSX2023 SENSOR TESTS ----\n");

  InitAllSensors();

  if (debugMode)
    Serial.println("\n");
}

void loop() 
{
  if (debugMode)
    Serial.println("-- RSX2023 SENSOR DATA --\n");
    
  Serial.println(ReadAllSensors());

  delay(delayTime);
}