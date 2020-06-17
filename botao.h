#ifndef BOTAO_H
#define BOTAO_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif


	#define			BTN_VERDE	      85
	#define			BTN_DIREITA	    84
	#define			BTN_BAIXO	      70
	#define			BTN_CIMA	      80
	#define			BTN_VERMELHO	  82
	#define			BTN_ESQUERDA	  33
		

		typedef struct {
		    uint8_t b1:1;
		    uint8_t b2:1;
		    uint8_t b3:1;
		    uint8_t b4:1;
		    uint8_t b5:1;
		    uint8_t b6:1;
		    uint8_t deadTime:1;
		    uint8_t   :1;
		  } button_t;

		char detect_Button();
		char read_Button();
		void deadTimeButton_Isr();  
		void button_Init();
		
	#ifdef __cplusplus
	} // extern "C"
	#endif

#endif
