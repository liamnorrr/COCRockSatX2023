#include "RSX_CH9121_ETH.h"
#include "RSX2023_Sensors.h"

const int BAUD_RATE = 9600;
const bool DEBUG = true;

void setup()
{
  if (DEBUG)
    Serial.begin(BAUD_RATE);

  eth_begin(DEBUG);
  InitAllSensors(DEBUG);
}

void loop()
{
  String message = ReadAllSensors();
  eth_send_message(DEBUG, message);
  Serial.println("\n---- SENT MESSAGE START ----\n" + message + "\n---- SENT MESSAGE END ----");

  //Serial.println("\n---- RECIEVED MESSAGE START ----\n" + eth_receive_message(DEBUG) + "\n---- RECIEVED MESSAGE END ----");
  //if (DEBUG)
  //  eth_debug();

  delay(1000);
}