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
	#define			LCD_DB4 					43	
	#define			LCD_DB5 					45
	#define			LCD_DB6 					47
	#define			LCD_DB7 					49
	#define			LCD_RS 						9
	#define			LCD_EN 						8
	#define			LCD_PWM						13

	// 				BOTÕES
//prototipo 1
  
//    #define         B_bt1                       41 
//    #define         B_bt2                       39
//    #define         B_bt3                       37
//    #define         B_bt4                       35
//    #define         B_bt5                       33
//    #define         B_bt6                       31

//prototipo 2
    #define         B_bt1                       31
    #define         B_bt2                       35
    #define         B_bt3                       41
    #define         B_bt4                       39
    #define         B_bt5                       33
    #define         B_bt6                       37


    #define         P_VALVULA_PRESSAO_EXP		    46	
    #define         P_SENSOR_PRESSAO			      0
    #define         S_SENSOR_INDUTIVO			      2
    #define         B_ALARM_BUZZER              3


    //LED
    #define  L_LED_AMARELO                        23
    #define  L_LED_AZUL                           25
    #define  L_LED_VERDE                          29
    #define  L_LED_VERMELHO                       27
  

  #ifdef __cplusplus
  } // extern "C"
  #endif

#endif
