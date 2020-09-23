#ifndef MOTOR_H
#define MOTOR_H

#include "bibliotecas.h"

#ifdef __cplusplus
extern "C"{
#endif

void stop_Motor();                                                                            
void direct_Motor(uint8_t p, uint8_t duty);
void motor_Init();                                                

#ifdef __cplusplus
} // extern "C"
#endif

#endif