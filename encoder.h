#ifndef ENCODER_H
#define ENCODER_H

#include "bibliotecas.h"

  #ifdef __cplusplus
  extern "C"{
  #endif

    #define     JUCA_FELIZ_COVID_19     0x00
    #define     MASK                    0x03

    typedef union {
      struct {
          uint32_t Even_PAR:1;
          uint32_t Mag_DEC :1;
          uint32_t Mag_INC :1;
          uint32_t LIN     :1;
          uint32_t COF     :1;
          uint32_t OCF     :1;
          uint32_t d0      :1;
          uint32_t d1      :1;
          uint32_t d2      :1;
          uint32_t d3      :1;
          uint32_t d4      :1;
          uint32_t d5      :1;
          uint32_t d6      :1;
          uint32_t d7      :1;
          uint32_t d8      :1;
          uint32_t d9      :1;
          uint32_t d10     :1;
          uint32_t d11     :1;
          uint32_t         :14;// bits não usados
      } bit;

      struct {
          uint32_t         :6;
          uint32_t posi    :12;
          uint32_t         :14; // bits não usados
      } data;

          uint32_t u_data;

    } AS5045_t;

    void read_Encoder();
    void encoder_Init();
    uint16_t read_Posicao();


  #ifdef __cplusplus
  } // extern "C"
  #endif

#endif
