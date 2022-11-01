#include "RSX_CH9121_ETH.h"
#include "RSX2023_Sensors.h"

const int BAUD_RATE = 9600;
const bool DEBUG = true;

void setup()
{
  if (DEBUG)                  //Sender & Reciever
    Serial.begin(BAUD_RATE);  //Sender & Reciever

  eth_begin(DEBUG);           //Sender & Reciever
  InitAllSensors(DEBUG);      //Sender Only
}

void loop()
{
  String message = ReadAllSensors();                                                              //Sender Only
  eth_send_message(DEBUG, message);                                                               //Sender Only
  Serial.println("\n---- SENT MESSAGE START ----\n" + message + "\n---- SENT MESSAGE END ----");  //Sender Only

  //Serial.println("\n---- RECIEVED MESSAGE START ----\n" + eth_receive_message(DEBUG) + "\n---- RECIEVED MESSAGE END ----"); //Reciever Only
  //if (DEBUG)                                                                                                                //Reciever Only
  //  eth_debug();                                                                                                            //Reciever Only

  delay(1000);    //Sender & Reciever
}