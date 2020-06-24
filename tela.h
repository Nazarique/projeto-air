#ifndef TELA_H
#define TELA_H

#include "bibliotecas.h"

#ifdef __cplusplus
extern "C"{
#endif

    //            telas
#define     D_TELA_CONFIG_0     '0'
#define     D_TELA_CONFIG_1     '1'
#define     D_MENU_PRESSAO      '2'
#define     D_MENU_VOLUME       '3'
#define     D_MENU_PEEP         '4'
#define     D_MENU_CALIBRA          '5'
#define     D_TELA_INICIAL      '6'
#define     D_TELA_COLLAB         '9'

    //            SET
#define     D_INCREMENTO       1 
#define     D_DECREMENTO       2


    //    LIMITES das variáveis da IHM INF e SUP 
#define     L_VOLUME_SUP      300
#define     L_VOLUME_INF      150

#define     L_PEEP_SUP            25
#define     L_PEEP_INF            0

#define     L_PRESSAO_SUP     60
#define     L_PRESSAO_INF     2

#define     L_PROP_RESP_SUP     30
#define     L_PROP_RESP_INF     10

#define     L_TEMP_INSP_SUP     1800
#define     L_TEMP_INSP_INF     1000

#define     L_PAUSE_EXP_SUP     500
#define     L_PAUSE_EXP_INF     350

    typedef struct {  
        uint8_t h_peep;
        uint8_t h_pressao;
        uint8_t h_prop;
        uint16_t h_volume;
        uint16_t h_freq;
        uint16_t h_temp_insp;
        uint16_t h_pause_exp;
    } config_t;

    void machine_state();
    void screen_static(char p);           //tela Static
    void screen_dynamic(config_t *IHM_aux, char p, uint8_t cursor); 
    void screen_Init();

    void set_IHM_volume(config_t *IHM_aux, uint8_t p);
    void set_IHM_peep(config_t *IHM_aux, uint8_t p);
    void set_IHM_pressao(config_t *IHM_aux, uint8_t p);
    void set_IHM_proporcao(config_t *IHM_aux, uint8_t p);
    void set_IHM_tempInsp(config_t *IHM_aux, uint8_t p);
    void set_IHM_pauseExp(config_t *IHM_aux, uint8_t p);

  #ifdef __cplusplus
  } // extern "C"
  #endif


#endif
