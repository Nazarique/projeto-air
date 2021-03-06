#ifndef TELA_H
#define TELA_H

#include "bibliotecas.h"

#ifdef __cplusplus
extern "C"{
#endif

#define freq(a, b, c) ((uint16_t)(60000./(a + b + c)))
#define T_insp(a, b) ((uint16_t)(a + b ))

typedef struct {  
    uint8_t  h_peep;
    uint8_t  h_pressao;
    uint16_t h_prop;
    uint16_t h_volume;
    uint16_t h_freq;
    uint16_t h_temp_insp;
    uint16_t h_pause_exp;
} config_t;

config_t get_IHM_default();
void set_IHM_default(config_t *IHM);
void machine_state();
void screen_static(char p);//tela Static
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
