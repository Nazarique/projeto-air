#include "bibliotecas.h"

volatile uint16_t posicao_encoder = 0;

void read_Encoder()
{
  AS5045_t dados_encoder;

  memset(&dados_encoder, 0, sizeof(AS5045_t));

  digitalWrite(SS, LOW);//  inicia SPI
                    
  dados_encoder.u_data |= (SPI.transfer16(JUCA_FELIZ_COVID_19) << 2); 
  dados_encoder.u_data |= ((SPI.transfer16(JUCA_FELIZ_COVID_19) >> 14) & MASK); 

  digitalWrite(SS, HIGH);// termina SPI
  posicao_encoder = dados_encoder.data.posi;
  
  // if(!dados_encoder.bit.LIN)
  // {
  //   //não teve error
  // }  
}

uint16_t read_Posicao()
{
  return posicao_encoder;
}

void encoder_Init()
{
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
}
