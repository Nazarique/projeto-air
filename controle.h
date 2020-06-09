#ifndef CONTROLE_H
#define CONTROLE_H

#include "bibliotecas.h"

  #ifdef __cplusplus
  extern "C"{
  #endif
    
    typedef void (*tipoFuncao_p)(system_status *p_sys_status);

    uint8_t degrau(uint8_t pwm, uint8_t pwm_atual);
    void set_Degrau();
    void maqEstados_Control();
    void control_Inspiracao(system_status *p_sys_status);
    void control_Expiracao(system_status *p_sys_status);
    void control_init();

  #ifdef __cplusplus
  } // extern "C"
  #endif

#endif
