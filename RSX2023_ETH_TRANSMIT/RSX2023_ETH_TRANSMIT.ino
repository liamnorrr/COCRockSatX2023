// Teensy 4.1 Config
const int BAUD_RATE = 9600;
const bool DEBUG = true;

// Ethernet Config
#include "RSX_CH9121_ETH.h"

// Main Function
void setup()
{
  if (DEBUG)
    Serial.begin(BAUD_RATE);
  eth_begin(DEBUG);
}

void loop()
{
  String message = "Bruhhhhhhh";
  eth_send_message(DEBUG, message);

  if (DEBUG)
    Serial.println("Message: " + eth_receive_message(DEBUG));
  delay(100);
  eth_debug();
}