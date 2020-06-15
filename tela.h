#ifndef TELA_H
#define TELA_H

#include "bibliotecas.h"

	#ifdef __cplusplus
	extern "C"{
	#endif

//						telas
		#define 		D_TELA_CONFIG_0			'0'
		#define 		D_TELA_CONFIG_1			'1'
		#define 		D_MENU_PRESSAO			'2'
		#define 		D_MENU_VOLUME		        '3'
		#define			D_MENU_PEEP      		'4'
		#define			D_MENU_CALIBRA           	'5'
		#define 		D_TELA_INICIAL			'6'
		#define			D_TELA_COLLAB      		'9'

//						variáveis de controle
		#define 		D_SET_VOLUME			'1'
		#define 		D_SET_PEEP	       		'2'
		#define 		D_SET_PRESSAO			'3'
		#define 		D_SET_FREQ_RESPI		'4'
		#define 		D_SET_TEMP_INSPI		'5'
		#define 		D_SET_PAUSE_EXP			'6'
		#define			D_SET_CALIBRA     		'7'

//						SET
	    #define 		D_INCREMENTO 			 1 
	    #define 		D_DECREMENTO 			 2
	    

// 		LIMITES das variáveis da IHM INF e SUP 
		#define 		L_VOLUME_SUP			400
		#define 		L_VOLUME_INF			100

		#define 		L_PEEP_SUP		        5
		#define 		L_PEEP_INF		        3

		#define 		L_PRESSAO_SUP			60
		#define 		L_PRESSAO_INF			10

		#define 		L_FREQ_RESP_SUP			30
		#define 		L_FREQ_RESP_INF			10

		#define 		L_TEMP_INSP_SUP			2000
		#define 		L_TEMP_INSP_INF			900

		#define 		L_PAUSE_EXP_SUP			500
		#define 		L_PAUSE_EXP_INF			350

		typedef struct {  
	        uint16_t h_volume 	= 0;
	        uint16_t h_peep   	= 0;
	        uint16_t h_pressao	= 0;
	        uint16_t h_freq		= 0;
	        uint16_t h_temp_insp= 0;
	        uint16_t h_pause_exp= 0;
	    } config_t;

		void machine_state();
		void screen_static(char p);						//tela Static
		void screen_dynamic(control_t *controle, config_t *IHM_aux, char p);	
		void screen_Init();

		void set_IHM_volume(config_t *IHM_aux, uint8_t p);
		void set_IHM_peep(config_t *IHM_aux, uint8_t p);
		void set_IHM_pressao(config_t *IHM_aux, uint8_t p);
		void set_IHM_freqResp(config_t *IHM_aux, uint8_t p);
		void set_IHM_tempInsp(config_t *IHM_aux, uint8_t p);
		void set_IHM_pauseExp(config_t *IHM_aux, uint8_t p);

	#ifdef __cplusplus
	} // extern "C"
	#endif


#endif
