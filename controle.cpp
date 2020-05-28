#include "bibliotecas.h"

volatile uint8_t deadTime_Motor, degrau_Motor = 0;
//variaveis globais para os contadores via interrupção

AS5045 encoder(AS_SPI_SS, AS_SPI_SCK, AS_SPI_MISO);

static motorAux_t motor = {0};
static posicao_t posi = {0};

void deadTimeMotor_Isr()                                                      
{
  /* Contadores usados para controle do motor, cont20 = 20ms, cont5 = 5ms.*/

  static unsigned char cont20 = 200;
  static unsigned char cont5 = 5;

  if(deadTime_Motor)                                                        
  {
    if(--cont20==0)                                                           
    { 
      cont20 = 200;                                                            
      deadTime_Motor = 0; 
    }
  }

  if(degrau_Motor)
  {
    if(--cont5==0)                                                           
    { 
      cont5 = 5;                                            
      degrau_Motor = 0;                                                                                                              
    }
  }
}

uint8_t degrau(uint8_t pwm, uint8_t pwm_atual)
{
  uint8_t passo = 5;

  if(pwm_atual == pwm)
  {
    return pwm_atual;
  }
  else if(pwm_atual > pwm)
  {
    return (pwm_atual - passo);
  }
  else if(pwm_atual < pwm)
  {
    return (pwm_atual + passo);
  }
}

void set_Degrau(motorAux_t *motor)
{
  /* Função que verifica se teve um deadTime, após a verificação ela aciona
      o motor na posição definida. */
  if(motor->stop==1 && deadTime_Motor==0)
  {
    motor->stop = 0;
    motor->Adirecao = motor->direcao;

    direct_Motor(motor->direcao);
  }
  else if(motor->stop==0 && degrau_Motor==0)
  {
    motor->pwm_atual = degrau(motor->pwm_requerido, 
                              motor->pwm_atual);
    degrau_Motor = 1;
  }
  set_Duty(motor->pwm_atual); //duvida
}

void change_Motor(motorAux_t *motor)   
{
  if(motor->Adirecao != motor->direcao)       
  {
    stop_Motor();
    motor->Adirecao = motor->direcao;

    motor->stop     = 1;             
    deadTime_Motor  = 1;
    
    motor->pwm_atual= 0;
  }
  else
  {
    direct_Motor(motor->direcao);  
  }
}

void inverte_Rotacao()
{
  uint16_t posicao_encoder;

  posicao_encoder = ((uint16_t)(encoder.read()*0.08789));

  if (posicao_encoder > posi.angulo_final && motor.Adirecao == 1)
  {
    motor.pwm_requerido = 250;
    motor.direcao = 0;
    change_Motor(&motor);
  }

  else if (posicao_encoder < posi.angulo_inicial && motor.Adirecao == 0) 
  {
    motor.direcao = 1;
    motor.pwm_requerido = 10;
    change_Motor(&motor);
  }
  set_Degrau(&motor); 
}

void control_init()
{
  encoder.begin();
  posi.angulo_final = 120;
  posi.angulo_inicial = 60;

  motor.pwm_requerido = 120;

}
