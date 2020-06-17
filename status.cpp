
#include "bibliotecas.h"

static system_status_t my_sys_status = {0};

system_status_t *get_sys_status()
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
   my_sys_status.s_control.c_angulo_final = my_sys_status.s_control.c_angulo_inicial - angulo;
}

void *set_control_PEEP(uint8_t peep)
{
   my_sys_status.s_control.c_pressao_PEEP = peep;
}

void *set_control_tempoInspiratorioIHM(uint16_t tempo_insp)
{
   my_sys_status.s_control.c_tempo_insp_IHM = tempo_insp;
}

void *set_control_tempoExpiratorioIHM(uint16_t frequencia)
{
  float provisorio;
  provisorio = 60000/frequencia - (float)(my_sys_status.s_control.c_tempo_insp_cont + my_sys_status.s_control.c_tempo_exp_cont +
                                              my_sys_status.s_control.c_tempo_exp_pause);
  if(provisorio < 0){
    provisorio = 0;
  }
  my_sys_status.s_control.c_tempo_exp_ocioso = provisorio;
}

void *set_control_pause(uint16_t delay)
{
   my_sys_status.s_control.c_tempo_exp_pause = delay;
}
