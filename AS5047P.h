#ifndef AS5047P_H
#define AS5047P_H

#include "bibliotecas.h"

#ifdef __cplusplus
extern "C"{
#endif

#define AS5047P_select_pin 48
/** volatile **/
#define NOP 0x0000
#define ERRFL 0x0001
#define PROG   0x0003
#define DIAAGC 0x3FFC
#define CORDICMAG 0x3FFD
#define ANGLEUNC  0x3FFE
#define ANGLECOM  0x3FFF

/** non-volatile **/
#define ZPOSM 0x0016
#define ZPOSL 0x0017
#define SETTINGS1 0x0018
#define SETTINGS2 0x0019

#define RD  0x40    // bit 14 "1" is Read + parity even
#define WR  0x3F    //bit 14 ="0" is Write

void AS5047P_Init();
void AS5047P_Write( int SSPin, int address, int value);
unsigned int AS5047P_Read( int SSPin, unsigned int address);
int parity(unsigned int x); 
#ifdef __cplusplus
} // extern "C"
#endif

#endif