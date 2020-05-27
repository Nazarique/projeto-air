#ifndef CONTROLE_H
#define CONTROLE_H

#include "bibliotecas.h"

  #ifdef __cplusplus
  extern "C"{
  #endif

    typedef struct 
      {
        uint16_t angulo_final;
        uint16_t angulo_inicial;
      } posicao_t;

    typedef struct 
      {
        uint8_t stop  :1;
        uint8_t direcao; 
        uint8_t Adirecao; 

        uint8_t pwm_requerido;
        uint8_t pwm_atual;
      } motorAux_t;

    void deadTimeMotor_Isr();
    void inverte_Rotacao();
    void change_Motor(motorAux_t *motor);
    void set_Degrau(motorAux_t *motor);
    uint8_t degrau(uint8_t pwm, uint8_t pwm_atual);

    void control_init();

  #ifdef __cplusplus
  } // extern "C"
  #endif

#endif
