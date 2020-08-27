#ifndef BOTAO_H
#define BOTAO_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif


	#define			BTN_VERDE	      'g'
	#define			BTN_DIREITA	    'd'
	#define			BTN_BAIXO	      'b'
	#define			BTN_CIMA	      'c'
	#define			BTN_VERMELHO	  'r'
	#define			BTN_ESQUERDA	  'e'
		

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
