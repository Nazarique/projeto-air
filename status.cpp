
#include "bibliotecas.h"

static system_status my_sys_status = {0};

system_status *get_sys_status()
{
	return &my_sys_status;
}

void *set_sys_status(uint8_t status)
{	
	/* Função que liga ou desliga todo sistema de controle,
		qdo ligado o motor funciona, qdo desligado o 
		motor não é acionado.
	*/

	if(status == 0)
	{
		//if de proteção, o status só pode ser 1 ou 0;
		my_sys_status.s_respirador = 0;
		stop_Motor();
	}
	else if(status == 1)
	{
		my_sys_status.s_respirador = 1;
	}	
}

void *set_control_angulo(uint16_t angulo) 
{
   my_sys_status.s_control.c_angulo_final = angulo;
}

void *set_control_pwm(uint8_t pwm)
{
   my_sys_status.s_control.c_pwm_insp = pwm;
}

void *set_control_PEEP(uint8_t peep)
{
   my_sys_status.s_control.c_pressao_PEEP = peep;
}
