#include "RSX2023_Sensors.h"

extern int PIN_SCK;
extern int PIN_MISO;
extern int PIN_MOSI;
extern int PIN_CS_BME;
extern int PIN_CS_BMP;

extern float SEALEVELPRESSURE_HPA;
extern int delayTime;

extern bool debugMode;

Adafruit_BME280 BME280(PIN_CS_BME);  // hardware SPI
//Adafruit_BME280 BME280(PIN_CS_BME, PIN_MOSI, PIN_MISO, PIN_SCK); // software SPI
Adafruit_BMP280 BMP280(PIN_CS_BMP);  // hardware SPI
//Adafruit_BMP280 BMP280(PIN_CS_BMP, PIN_MOSI, PIN_MISO, PIN_SCK); // software SPI

String ReadAllSensors()
{
  String BME280_data = "";
  String BMP280_data = "";

  BME280_data += "BME280:\n";
  BME280_data += "Temperature:\t"  + String(BME280_ReadData(0)) + " °C\n";
  BME280_data += "Pressure:\t"     + String(BME280_ReadData(1)) + " hPa\n";
  BME280_data += "Altitude:\t"     + String(BME280_ReadData(2)) + " m\n";
  BME280_data += "Humidity:\t"     + String(BME280_ReadData(3)) + " %\n";
  BME280_data += "\n";

  BMP280_data += "BMP280:\n";
  BMP280_data += "Temperature:\t"  + String(BMP280_ReadData(0)) + " °C\n";
  BMP280_data += "Pressure:\t"     + String(BMP280_ReadData(1)) + " Pa\n";
  BMP280_data += "Altitude:\t"     + String(BMP280_ReadData(2)) + " m\n";
  BMP280_data += "\n";

  String data = "";

  data += BME280_data;
  data += BMP280_data;

  return data;
}

void InitAllSensors()
{
  BME280_Init();
  BMP280_Init();
}

float BME280_ReadData(int type)
{
  if (type == 0) //Temperature
    return BME280.readTemperature();
  else if (type == 1) //Pressure
    return (BME280.readPressure() / 100.0F);
  else if (type == 2) //Altitude
    return BME280.readAltitude(SEALEVELPRESSURE_HPA);
  else if (type == 3) //Humidity
    return BME280.readHumidity();

  return -6969;
}

float BMP280_ReadData(int type)
{
  if (type == 0) //Temperature
    return BMP280.readTemperature();
  else if (type == 1) //Pressure
    return BMP280.readPressure();
  else if (type == 2) //Altitude
    return BMP280.readAltitude(1013.25);

  return -6969;
}

void BME280_Init()
{
  if (debugMode)
    Serial.println("SETTING UP BME280...");

  while (!BME280.begin()) 
  {
    if (debugMode)
    {
      Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
      Serial.print("SensorID was: 0x");
      Serial.println(BME280.sensorID(), 16);
      Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      Serial.print("        ID of 0x60 represents a BME 280.\n");
      Serial.print("        ID of 0x61 represents a BME 680.\n");
    }

    delay(delayTime);
  }

  if (debugMode)
    Serial.println("FINISHED SETTING UP BME280.");
}

void BMP280_Init()
{
  if (debugMode)
    Serial.println("SETTING UP BMP280...");

  while (!BMP280.begin()) 
  {
    if (debugMode)
    {
      Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!");
      Serial.print("SensorID was: 0x");
      Serial.println(BMP280.sensorID(), 16);
      Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      Serial.print("        ID of 0x60 represents a BME 280.\n");
      Serial.print("        ID of 0x61 represents a BME 680.\n");
    }

    delay(delayTime);
  }

  BMP280.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  if (debugMode)
    Serial.println("FINISHED SETTING UP BMP280.");
}