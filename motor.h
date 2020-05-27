#ifndef MOTOR_H
#define MOTOR_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif

		#define			D_ROTACAO_0_DESCIDA 	0
		#define			D_ROTACAO_1_SUBIDA 		1

		void stop_Motor();                                                                            
		void direct_Motor(uint8_t p);                                                       
		void set_Duty(uint8_t duty);
		void motor_Init();                                                

	#ifdef __cplusplus
	} // extern "C"
	#endif

#endif