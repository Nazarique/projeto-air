#ifndef BOTAO_H
#define BOTAO_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif


		#define			D_CARACTER_BOTAO_1	85
		#define			D_CARACTER_BOTAO_2	85
		#define			D_CARACTER_BOTAO_3	70
		#define			D_CARACTER_BOTAO_4	80
		#define			D_CARACTER_BOTAO_5	82
		#define			D_CARACTER_BOTAO_6	33
		

		typedef struct {
		    char b1:1;
		    char b2:1;
		    char b3:1;
		    char b4:1;
		    char b5:1;
		    char b6:1;
		    char deadTime:1;
		    char   :1;
		  } button_t;

		char detect_Button();
		char read_Button();
		void deadTimeButton_Isr();  
		void button_Init();
		
	#ifdef __cplusplus
	} // extern "C"
	#endif

#endif
