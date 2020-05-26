#ifndef PINOUT_H
#define PINOUT_H

#include "bibliotecas.h"

  #ifdef __cplusplus
  extern "C"{
  #endif

	//		 		ENCODER_AS5045_SPI
	#define 		AS_SPI_SCK 					52  // clk
	#define 		AS_SPI_MISO 				50  // DO pin
	#define 		AS_SPI_MOSI 				51  // não usado
	#define 		AS_SPI_SS 					48  // CS for this device

	//				MOTORDRIVER_BTS7960
	#define			DRIVE_IN1 					13
	#define			DRIVE_IN2 					12
	#define			DRIVE_PWM 					11

	//		 		DISPLAY_LCD_20x4
	#define			LCD_DB4 					4	
	#define			LCD_DB5 					5
	#define			LCD_DB6 					6
	#define			LCD_DB7 					7
	#define			LCD_RS 						8
	#define			LCD_EN 						9

	// 				BOTÕES
	    #define         B_bt1                       32
	    #define         B_bt2                       34
	    #define         B_bt3                       36
	    #define         B_bt4                       38
	    #define         B_bt5                       40
	    #define         B_bt6                       30

  #ifdef __cplusplus
  } // extern "C"
  #endif

#endif
