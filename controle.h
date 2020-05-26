#ifndef CONTROLE_H
#define CONTROLE_H

#include "bibliotecas.h"

  #ifdef __cplusplus
  extern "C"{
  #endif

    typedef struct {
      struct 
      {
        uint8_t flag_degrau :1;
        uint8_t direcao;
        uint8_t pwm_requerido;
        uint8_t pwm_atual;
      } motor;

      struct 
      {
        uint16_t angulo_final;
        uint16_t angulo_inicial;
      } posicao;

    } control_t;

    void degrauTime_Isr();
    uint8_t degrau(uint8_t pwm, uint8_t pwm_atual);
    void set_Degrau();
    void inverte_Rotacao();
    //void prenche_estrutura();

  #ifdef __cplusplus
  } // extern "C"
  #endif

#endif
