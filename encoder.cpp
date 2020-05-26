#include "bibliotecas.h"

volatile uint16_t posicao_encoder = 0;

void encoder()
{
  AS5045_t dados_encoder;

  memset(&dados_encoder, 0, sizeof(AS5045_t));

  digitalWrite(AS_SPI_SS, LOW);//  inicia SPI
                    
  dados_encoder.u_data |= (SPI.transfer(JUCA_FELIZ_COVID_19) << 11); 
  dados_encoder.u_data |= (SPI.transfer(JUCA_FELIZ_COVID_19) << 3);
  dados_encoder.u_data |= ((SPI.transfer(JUCA_FELIZ_COVID_19) >> 5) & 0x06); 

  digitalWrite(AS_SPI_SS, HIGH);// termina SPI
  posicao_encoder = dados_encoder.data.posi;
  
}

uint16_t read_Posicao()
{
  return posicao_encoder;
}

void encoder_Init()
{
  pinMode(AS_SPI_SS, OUTPUT);
  digitalWrite(AS_SPI_SS, HIGH);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(3);
}
//                  BA 9876 5432 10st atus  

// xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx
//                               BA98 7654 
// xxxx xxxx xxxx xBA9 8765 4xxx xxxx xxxx   11
//                               3210 stat
// xxxx xxxx xxxx xBA9 8765 4321 0sta txxx   3
//                               usxx xxxx  
//                               xxxx xusx   5  & 0x06
