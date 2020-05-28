#ifndef BOTAO_H
#define BOTAO_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif


		#define			D_CARACTER_BOTAO_1	80
		#define			D_CARACTER_BOTAO_2	81
		#define			D_CARACTER_BOTAO_3	82
		#define			D_CARACTER_BOTAO_4	83
		#define			D_CARACTER_BOTAO_5	84
		#define			D_CARACTER_BOTAO_6	85
		

		typedef struct {
		      unsigned char b1:1;
		      unsigned char b2:1;
		      unsigned char b3:1;
		      unsigned char b4:1;
		      unsigned char b5:1;
		      unsigned char b6:1;
		      unsigned char deadTime:1;
		      unsigned char	:1;
		  } button_t;

		char detect_Button();
		char read_Button();
		void deadTimeButton_Isr();  
		void button_Init();
		
	#ifdef __cplusplus
	} // extern "C"
	#endif

#endif
