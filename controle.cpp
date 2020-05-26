#include "bibliotecas.h"

volatile control_t control = {0};

void degrauTime_Isr()                                                      
{
  static unsigned char cont5 = 5;

  if(control.motor.flag_degrau)
  {
    if(--cont5==0)                                                           
    { 
    	cont5 = 5;                                            
    	control.motor.flag_degrau = 0;                                                                                                              
    }
  }
}

uint8_t degrau(uint8_t pwm, uint8_t pwm_atual)
{
  uint8_t passo = 5;

	if(pwm_atual == pwm)
	{
    control.motor.flag_degrau = 0;
		return pwm_atual;
	}
	else if(pwm_atual > pwm)
	{
    control.motor.flag_degrau = 1;
		return (pwm_atual - passo);
	}
	else if(pwm_atual < pwm)
	{
    control.motor.flag_degrau = 1;
		return (pwm_atual + passo);
	}
}

void set_Degrau()
{
  if(!control.motor.flag_degrau)
    {
      control.motor.pwm_atual = degrau(control.motor.pwm_requerido,
                                       control.motor.pwm_atual);//duvida
    }
  set_Duty(control.motor.pwm_atual); //duvida
}


void inverte_Rotacao()
{

   volatile uint16_t posicao_encoder = 0;
   
   posicao_encoder = 10;

   //posicao_encoder > control.posicao.angulo_inicial

  if (control.motor.pwm_atual < 20  && control.motor.direcao == 1)
  {
    control.motor.direcao = 0;
    change_Motor(control.motor.direcao);
  } 
  //posicao_encoder < control.posicao.angulo_final

  if (control.motor.pwm_atual > 200 && control.motor.direcao == 0) 
  {
    control.motor.direcao = 1;
    change_Motor(control.motor.direcao);
  }
  set_Degrau(); 
}

// void prenche_estrutura(control_t *c, uint8_t pwm,
//                        uint16_t angulo)
// {
//   c-> motor.pwm_requerido = pwm;
//   c-> posicao.angulo_final = angulo;
// }
