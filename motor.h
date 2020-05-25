#ifndef MOTOR_H
#define MOTOR_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif

		#define			D_ROTACAO_0_DESCIDA 	0
		#define			D_ROTACAO_1_SUBIDA 		1

//						MOTORDRIVER_BTS7960
		#define			DRIVE_IN1 					13
		#define			DRIVE_IN2 					12
		#define			DRIVE_PWM 					11

		typedef struct 
			{
			  uint8_t deadTime :1;
			  uint8_t stop     :1;
			  uint8_t direcao  :1; 
			  uint8_t Adirecao :1; 
			} motorAux_t;

		void stop_Motor();                                                                            
		void direct_Motor(uint8_t p);                                                       
		void set_Duty(uint8_t duty);
		void motor_Init();
		void deadTimeMotor_Isr();
		void change_Motor(uint8_t p);                                                 

	#ifdef __cplusplus
	} // extern "C"
	#endif

#endif