#include "bibliotecas.h"

volatile uint16_t posicao_encoder = 0;

void encoder()
{
  AS5045_t dados_encoder  = {};

  memset(&dados_encoder, 0, sizeof(AS5045_t));

  digitalWrite(SS, LOW);//  inicia SPI
                    
  dados_encoder.u_data |= (SPI.transfer16(JUCA_FELIZ_COVID_19) << 2); 
  dados_encoder.u_data |= ((SPI.transfer(JUCA_FELIZ_COVID_19) >> 6) & MASK); 

  digitalWrite(SS, HIGH);// termina SPI
  posicao_encoder = dados_encoder.data.posi;
  
}

uint16_t read_Posicao()
{
  return posicao_encoder;
}

void encoder_Init()
{
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(3);
}
