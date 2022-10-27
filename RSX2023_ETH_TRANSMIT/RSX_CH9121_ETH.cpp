#include "RSX_CH9121_ETH.h"
#include "Arduino.h"

#define SERIAL_ETH Serial1
const int CFG_PIN = 14;
const int RESET_PIN = 15;
const int RSTI_PIN = 16;

// Transmit Data
unsigned char CH9121_Mode = 3;                            // 0:TCP_SERVER  1:TCP_CLIENT 2:UDP_SERVER 3:UDP_CLIENT
unsigned char CH9121_LOCAL_IP[4] = {192, 168, 1, 100};    // LOCAL IP
unsigned char CH9121_GATEWAY[4] = {169, 254, 88, 1};      // GATEWAY
unsigned char CH9121_SUBNET_MASK[4] = {255, 255, 255, 0}; // SUBNET MASK
unsigned char CH9121_TARGET_IP[4] = {192, 168, 1, 200};   // TARGET_IP
unsigned char CH9121_Random_port = 0;                     // Random port    1:on   0:off
short unsigned int CH9121_PORT1 = 4369;                   // LOCAL PORT1
short unsigned int CH9121_TARGET_PORT = 4369;             // TARGET PORT
long unsigned int CH9121_BAUD_RATE = 9600;                // BAUD RATE

// Receive Data
// unsigned char CH9121_Mode = 2;                               //0:TCP_SERVER  1:TCP_CLIENT 2:UDP_SERVER 3:UDP_CLIENT
// unsigned char CH9121_LOCAL_IP[4] = { 192, 168, 1, 200 };     // LOCAL IP
// unsigned char CH9121_GATEWAY[4] = { 169, 254, 88, 1 };       // GATEWAY
// unsigned char CH9121_SUBNET_MASK[4] = { 255, 255, 255, 0 };  // SUBNET MASK
// unsigned char CH9121_TARGET_IP[4] = { 192, 168, 1, 100 };    // TARGET_IP
// unsigned char CH9121_Random_port = 0;                        //Random port    1:on   0:off
// short unsigned int CH9121_PORT1 = 4369;                      // LOCAL PORT1
// short unsigned int CH9121_TARGET_PORT = 4369;                // TARGET PORT
// long unsigned int CH9121_BAUD_RATE = 9600;                 // BAUD RATE

#define Mode1 0x10               // Port 1: Setup Mode   0x00:TCP Server 0x01:TCP Client 0x02:UDP Server 0x03:UDP Client
#define LOCAL_IP 0x11            // Local IP
#define SUBNET_MASK 0x12         // Subnet Mask
#define GATEWAY 0x13             // Gateway
#define LOCAL_PORT1 0X14         // Port 1:Local Port
#define TARGET_IP1 0x15          // Port 1:Target IP
#define TARGET_PORT1 0x16        // Port 1:Target Port
#define PORT_RANDOM_ENABLE1 0x17 // Port 1:Port Random Enable
#define UART1_BAUD1 0x21         // Port 1:Baud rate of serial port 1

//#define ON_OFF_UART2 0X39         //Port 2: Enable/disable port 2
//#define Mode2 0x40                //Port 2: Setup Mode   0x00:TCP Server 0x01:TCP Client 0x02:UDP Server 0x03:UDP Client
//#define LOCAL_PORT2 0X41          //Port 2:Local Port
//#define TARGET_IP2 0x42           //Port 2:Target IP
//#define TARGET_PORT2 0x43         //Port 2:Target Port
//#define UART1_BAUD2 0x44          //Port 2:Baud rate of serial port 2
//#define PORT_RANDOM_ENABLE2 0x17  //Port 2:Port Random Enable.

/**************** DO NOT CHANGE BELOW ******************/
char tx[8] = {0x57, 0xAB};

/******************************************************************************
 function:  Send four bytes
 parameter:
   data: parameter
   command: command code
 Info:  Set mode, enable port, clear serial port, switch DHCP, switch port 2
******************************************************************************/
void CH9121_TX_4_bytes(unsigned char data, int command)
{
  for (int i = 2; i < 4; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = data;
  }
  delay(10);
  for (int o = 0; o < 4; o++)
    SERIAL_ETH.write(tx[o]);
  delay(10);
  for (int i = 2; i < 4; i++)
    tx[i] = 0;
}

/******************************************************************************
 function:  Send five bytes
 parameter:
   data: parameter
   command: command code
 Info:  Set the local port and target port
******************************************************************************/
void CH9121_TX_5_bytes(short unsigned int data, int command)
{
  unsigned char Port[2];
  Port[0] = data & 0xff;
  Port[1] = data >> 8;
  for (int i = 2; i < 5; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = Port[i - 3];
  }
  delay(10);
  for (int o = 0; o < 5; o++)
  {
    SERIAL_ETH.write(tx[o]);
  }
  delay(10);
  for (int i = 2; i < 5; i++)
    tx[i] = 0;
}
/******************************************************************************
 function: Send seven bytes
 parameter:
   data: parameter
   command: command code
 Info:  Set the IP address, subnet mask, gateway,
******************************************************************************/
void CH9121_TX_7_bytes(unsigned char data[], int command)
{
  for (int i = 2; i < 7; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = data[i - 3];
  }
  delay(10);
  for (int o = 0; o < 7; o++)
    SERIAL_ETH.write(tx[o]);
  delay(10);
  for (int i = 2; i < 7; i++)
    tx[i] = 0;
}

/******************************************************************************
 function: CH9121_TX_BAUD
 parameter:
   data: parameter
   command: command code
 Info:  Set baud rate
******************************************************************************/
void CH9121_TX_BAUD(long unsigned int data, int command)
{
  unsigned char Port[4];
  Port[0] = (data & 0xff);
  Port[1] = (data >> 8) & 0xff;
  Port[2] = (data >> 16) & 0xff;
  Port[3] = data >> 24;

  for (int i = 2; i < 7; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = Port[i - 3];
  }
  delay(10);
  for (int o = 0; o < 7; o++)
    SERIAL_ETH.write(tx[o]);
  delay(10);
  for (int i = 2; i < 7; i++)
    tx[i] = 0;
}

/******************************************************************************
 function: CH9121_Eed
 parameter:
 Info:  Updating configuration Parameters
******************************************************************************/
void CH9121_Eed()
{
  tx[2] = 0x0d;
  for (int o = 0; o < 3; o++)
    SERIAL_ETH.write(tx[o]);
  delay(100);
  tx[2] = 0x0e;
  for (int o = 0; o < 3; o++)
    SERIAL_ETH.write(tx[o]);
  delay(100);
  tx[2] = 0x5e;
  for (int o = 0; o < 3; o++)
    SERIAL_ETH.write(tx[o]);
}

void eth_begin(bool debug)
{
  pinMode(RSTI_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RSTI_PIN, HIGH);
  digitalWrite(RESET_PIN, HIGH);
  if (debug)
    Serial.println("Ethernet setup begin.");
  SERIAL_ETH.begin(CH9121_BAUD_RATE);
  SERIAL_ETH.setTimeout(10);

  pinMode(CFG_PIN, OUTPUT);
  digitalWrite(CFG_PIN, LOW);

  if (debug)
    Serial.println("Begin configuration.");
  delay(100);
  CH9121_TX_4_bytes(CH9121_Mode, Mode1); // Mode
  if (debug)
    Serial.println("Mode set.");
  delay(100);
  CH9121_TX_7_bytes(CH9121_LOCAL_IP, LOCAL_IP); // LOCALIP
  if (debug)
    Serial.println("Local IP set.");
  delay(100);
  CH9121_TX_7_bytes(CH9121_SUBNET_MASK, SUBNET_MASK); // SUBNET MASK
  if (debug)
    Serial.println("Subnet mask set.");
  delay(100);
  CH9121_TX_7_bytes(CH9121_GATEWAY, GATEWAY); // GATEWAY
  if (debug)
    Serial.println("Gateway set.");
  delay(100);
  CH9121_TX_7_bytes(CH9121_TARGET_IP, TARGET_IP1); // TARGET IP
  if (debug)
    Serial.println("Target IP set.");
  delay(100);
  CH9121_TX_5_bytes(CH9121_PORT1, LOCAL_PORT1); // Local port
  if (debug)
    Serial.println("Local port set.");
  delay(100);
  if (debug)
    Serial.println("Begin target port.");
  CH9121_TX_5_bytes(CH9121_TARGET_PORT, TARGET_PORT1); // Target Port
  if (debug)
    Serial.println("Target port set.");
  delay(100);
  CH9121_TX_BAUD(CH9121_BAUD_RATE, UART1_BAUD1); // Port 1 baud rate
  if (debug)
    Serial.println("Baud set.");
  delay(100);
  CH9121_Eed();

  delay(100);
  char trash[20];
  SERIAL_ETH.readBytes(trash, 20);
  digitalWrite(CFG_PIN, HIGH);
  if (debug)
    Serial.println("Ethernet setup completed.");
}

void eth_send_message(bool debug, String &message)
{
  if (debug)
    Serial.println("Begin send message.");
  if (eth_availableForWrite() > 0)
  {
    SERIAL_ETH.print(message);
  }
  else if (debug)
    SERIAL_ETH.println("No room for write.");
  if (debug)
    Serial.println("Send message complete.");
}

String eth_receive_message(bool debug)
{
  if (debug)
    Serial.println("Begin receive message.");
  String message = "TEST";
  if (eth_available() == 0)
  {
    if (debug)
      Serial.println("Nothing to read.");
    message = "";
  }
  else
  {
    message = SERIAL_ETH.readString();
  }
  if (debug)
    Serial.println("Recieve message complete.");
  return message;
}

int eth_available()
{
  return SERIAL_ETH.available();
}

int eth_availableForWrite()
{
  return SERIAL_ETH.availableForWrite();
}

void send_command(int command)
{
  SERIAL_ETH.write(0x57);
  SERIAL_ETH.write(0xAB);
  SERIAL_ETH.write(command);
}

void eth_debug()
{
  byte bytes[4];
  digitalWrite(CFG_PIN, LOW);
  send_command(0x60); // Get Working Mode
  SERIAL_ETH.readBytes(bytes, 1);
  Serial.print("Working Mode: ");
  Serial.println(bytes[0], DEC);
  send_command(0x61); // Get IP Address
  SERIAL_ETH.readBytes(bytes, 4);
  Serial.print("IP Address: ");
  Serial.print(bytes[0], DEC);
  Serial.print("-");
  Serial.print(bytes[1], DEC);
  Serial.print("-");
  Serial.print(bytes[2], DEC);
  Serial.print("-");
  Serial.println(bytes[3], DEC);
  send_command(0x62); // Get Mask
  SERIAL_ETH.readBytes(bytes, 4);
  Serial.print("Mask: ");
  Serial.print(bytes[0], DEC);
  Serial.print("-");
  Serial.print(bytes[1], DEC);
  Serial.print("-");
  Serial.print(bytes[2], DEC);
  Serial.print("-");
  Serial.println(bytes[3], DEC);
  send_command(0x64); // Get Local Port
  SERIAL_ETH.readBytes(bytes, 2);
  Serial.print("Local Port: ");
  int temp = (bytes[0] << 8) + bytes[1];
  Serial.println(String(temp));
  send_command(0x65); // Get Target IP
  SERIAL_ETH.readBytes(bytes, 4);
  Serial.print("Target IP: ");
  Serial.print(bytes[0], DEC);
  Serial.print("-");
  Serial.print(bytes[1], DEC);
  Serial.print("-");
  Serial.print(bytes[2], DEC);
  Serial.print("-");
  Serial.println(bytes[3], DEC);
  send_command(0x66); // Get Target Port
  SERIAL_ETH.readBytes(bytes, 2);
  Serial.print("Target Port: ");
  temp = (bytes[0] << 8) + bytes[1];
  Serial.println(String(temp));
  send_command(0x71); // Get Target Port
  SERIAL_ETH.readBytes(bytes, 4);
  Serial.print("Baud: ");
  temp = (bytes[3] << 24) + (bytes[2] << 16) + (bytes[1] << 8) + bytes[0];
  Serial.println(String(temp));
  digitalWrite(CFG_PIN, HIGH);
  delay(1000);
}