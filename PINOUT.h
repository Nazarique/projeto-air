#ifndef PINOUT_H
#define PINOUT_H

#include "bibliotecas.h"

  #ifdef __cplusplus
  extern "C"{
  #endif

	//		 		ENCODER_AS5045_SPI
	#define 		AS_SPI_SCK 					52    // clk - 
	#define 		AS_SPI_MISO 				50    // DO pin
	#define 		AS_SPI_SS 					48    // CS for this device


	//				MOTORDRIVER_BTS7960
	#define			DRIVE_EN_R 					53
	#define			DRIVE_EN_L 					51
	#define			DRIVE_PWM_L					12
	#define			DRIVE_PWM_R  				11

	//		 		DISPLAY_LCD_20x4
	#define			LCD_DB4 					49	
	#define			LCD_DB5 					47
	#define			LCD_DB6 					45
	#define			LCD_DB7 					43
	#define			LCD_RS 						8
	#define			LCD_EN 						9
	#define			LCD_PWM						13


	// 				BOTÕES
    #define         B_bt1                       41
    #define         B_bt2                       39
    #define         B_bt3                       37
    #define         B_bt4                       35
    #define         B_bt5                       33
    #define         B_bt6                       31

    #define         P_VALVULA_PRESSAO_EXP		46	
    #define         P_SENSOR_PRESSAO			1	

  #ifdef __cplusplus
  } // extern "C"
  #endif

#endif
