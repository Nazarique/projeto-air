#ifndef TELA_H
#define TELA_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif

		#define 		D_TELA_CONFIG_0			'0'
		#define 		D_TELA_CONFIG_1			'1'
		#define 		D_MENU_PRESSAO			'2'
		#define 		D_MENU_VOLUME			  '3'
		#define 		D_MENU_FREQ_RES			'4'
		#define 		D_MENU_TEMP_INS			'5'
		#define 		D_TELA_INICIAL			'6'
		#define			D_TELA_INICIAL_V 		'7'
		#define			D_TELA_COLLAB      		'9'


//				 		DISPLAY_LCD_20x4
		#define			LCD_DB4 				4	
		#define			LCD_DB5 				5
		#define			LCD_DB6 				6
		#define			LCD_DB7 				7
		#define			LCD_RS 					8
		#define			LCD_EN 					9

		void machine_state();
		void screen_static(char p);						//tela Static
		void screen_dynamic(char p);						//tela dynamic
		void screen_Init();

	#ifdef __cplusplus
	} // extern "C"
	#endif


#endif
