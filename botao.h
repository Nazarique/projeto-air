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

		// 				BOTÕES
	    #define         B_bt1                       32
	    #define         B_bt2                       34
	    #define         B_bt3                       36
	    #define         B_bt4                       38
	    #define         B_bt5                       40
	    #define         B_bt6                       30

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
