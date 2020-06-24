
#include "bibliotecas.h"

static system_status_t my_sys_status = {0};

system_status_t *get_sys_status()
{
	return &my_sys_status;
}

control_t *get_control()
{
  return &my_sys_status.s_control;
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

void *set_control_angulo(uint16_t volume_ihm) 
{
   float angulo = -1.85*volume_ihm + 3451;
   if(angulo < 2850) angulo = 2850;
   my_sys_status.s_control.c_angulo_final = (uint16_t) angulo;
}

void *set_control_PEEP(uint8_t peep)
{
   my_sys_status.s_control.c_pressao_PEEP = peep;
}

void *set_control_tempoInspiratorioIHM(uint16_t tempo_insp)
{
   my_sys_status.s_control.c_tempo_insp_IHM = tempo_insp;
}

void *set_control_tempoExpiratorioIHM(uint8_t proporcao) //  proporcao seria 10 (1,0), 15 (1,5)
{                                                        //
  float provisorio;
  provisorio = my_sys_status.s_control.c_tempo_insp_IHM * proporcao / 10 - 550;
  if(provisorio<0) provisorio = 0;
  my_sys_status.s_control.c_tempo_exp_ocioso = provisorio;
}

void *set_control_pause(uint16_t delay)
{
   my_sys_status.s_control.c_tempo_exp_pause = delay;
}

void *set_control_pause(uint8_t pressao-ihm)
{
   my_sys_status.s_control.c_pressao_cont = pressao-ihm;
}
