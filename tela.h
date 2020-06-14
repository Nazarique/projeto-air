#ifndef TELA_H
#define TELA_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif

		#define 		D_TELA_CONFIG_0			'0'
		#define 		D_TELA_CONFIG_1			'1'
		#define 		D_MENU_PRESSAO			'2'
		#define 		D_MENU_VOLUME		    '3'
		#define 		D_MENU_FREQ_RES			'4'
		#define 		D_MENU_TEMP_INS			'5'
		#define 		D_TELA_INICIAL			'6'
		#define			D_TELA_INICIAL_V 		'7'
		#define			D_TELA_COLLAB      		'9'


	    #define 		D_INCREMENTO 			1 
	    #define 		D_DECREMENTO 			2
	    

		typedef struct {  
	        uint8_t  pwm;
	        uint8_t  PEEP;
	        uint16_t angulo;
	    } config_t;

		void machine_state();
		void screen_static(char p);						//tela Static
		void screen_dynamic(control_t *controle, config_t *IHM_aux, char p);	
		void screen_Init();
		void set_IHM_PWM(config_t *IHM_aux, uint8_t p);
    void set_IHM_angulo(config_t *IHM_aux, uint8_t p);
    void set_IHM_PEEP(config_t *IHM_aux, uint8_t p);

	#ifdef __cplusplus
	} // extern "C"
	#endif


#endif
