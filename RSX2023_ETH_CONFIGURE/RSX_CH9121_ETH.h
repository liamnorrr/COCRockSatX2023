#ifndef RSX_CH9121_ETH
#define RSX_CH9121_ETH

#include "Arduino.h"

/*
The ethernet chip used in this application is the "Network and UART Transparent Transmission Chip CH9121"
Datasheet: https://www.waveshare.com/w/upload/a/a9/CH9121DS1.PDF or in GitHub repo
Commands: https://www.waveshare.com/w/upload/e/ef/CH9121_SPCC.pdf or in GitHub repo
*/

void eth_begin(bool debug);
void eth_send_message(bool debug, String &message);
String eth_receive_message(bool debug);
int eth_available();
int eth_availableForWrite();
void eth_debug();

#endif