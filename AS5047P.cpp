#include "bibliotecas.h"
unsigned int reading = 0;

//Op Arduino: D10 CS, D11 MOSI, D12 MISO, D13 SCK
//SPISettings settings(2000000, MSBFIRST, SPI_MODE1); 
SPISettings settings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE1); 

void AS5047P_Init()
{
  pinMode(AS5047P_select_pin, OUTPUT);
  SPI.begin();
  SPI.setDataMode(SPI_MODE1); // properties chip
  SPI.setBitOrder(MSBFIRST);  //properties chip

  Serial.begin(115200);  // start serial for output
  Serial.println(" AS5047P:");

  AS5047P_Write( AS5047P_select_pin , SETTINGS1, 0x0001); //DJL was 0x0004);
  AS5047P_Write( AS5047P_select_pin , SETTINGS2, 0x0000);
  AS5047P_Write( AS5047P_select_pin , ZPOSM, 0x0000); // is it really possible to initially set angle at 0 degrees??
  AS5047P_Write( AS5047P_select_pin , ZPOSL, 0x0000);
}


// ************************Write to AS5047P **************************
void AS5047P_Write( int SSPin, int address, int value)
{
  // take the SS pin low to select the chip:
  SPI.beginTransaction(settings);
  digitalWrite(SSPin, LOW);
  
  //  send in the address via SPI:
  
  byte v_l = address & 0x00FF;
  byte v_h = (unsigned int)(address & 0x3F00) >> 8;
  
  if (parity(address & 0x3F) == 1) v_h = v_h | 0x80; // set parity bit
  //v_h = v_h & (WR | 0x80);  // its  a write command and don't change the parity bit (0x80)
  
  SPI.transfer(v_h);
  SPI.transfer(v_l);
  
  digitalWrite(SSPin, HIGH);
  SPI.endTransaction();
  
  delayMicroseconds(100);
  
  SPI.beginTransaction(settings);
  digitalWrite(SSPin, LOW);
  
  //  send value via SPI:
  
  v_l = value & 0x00FF;
  v_h = (unsigned int)(value & 0x3F00) >> 8;
  
  if (parity(value & 0x3F) == 1) v_h = v_h | 0x80; // set parity bit
  //v_h = v_h & (WR | 0x80); // its a write command and don't change the parity bit (0x80)
 
  SPI.transfer(v_h);
  SPI.transfer(v_l);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(SSPin, HIGH);
  SPI.endTransaction();
}

//*******************Read from AS5047P ********************************
unsigned int AS5047P_Read( int SSPin, unsigned int address)
{
  unsigned int result = 0;   // result to return
  
  byte res_h = 0;
  byte res_l = 0;
  
  //take the SS pin low to select the chip:
  SPI.beginTransaction(settings);
  digitalWrite(SSPin, LOW);
  
  //  send in the address and value via SPI:
  byte v_l = address & 0x00FF;
  byte v_h = (unsigned int)(address & 0x3F00) >> 8;
  
  if (parity(address | (RD << 8)) == 1) v_h = v_h | 0x80; // set parity bit
  
  v_h = v_h | RD; // its  a read command
  
  res_h = SPI.transfer(v_h);
  res_l = SPI.transfer(v_l);
  
  res_h = res_h & 0x3F;  // filter bits outside data
  
  digitalWrite(SSPin, HIGH);
  SPI.endTransaction();
  delayMicroseconds(100);
  
  return (result = (res_h << 8) | res_l);
}

//*******************check parity ******************************************
int parity(unsigned int x) 
{

  int parity = 0;
  while (x > 0) {
    parity = (parity + (x & 1)) % 2;
    x >>= 1;
  }
  return (parity);
}
