#ifndef RSX_CH9121_ETH
#define RSX_CH9121_ETH

#include "Arduino.h"


void eth_begin(bool debug);
void eth_send_message(bool debug, String& message);
String eth_receive_message(bool debug);
int eth_available();
int eth_availableForWrite();
void eth_debug();

#endif