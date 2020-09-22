#include "bibliotecas.h"
volatile system_status_t my_sys_status;

system_status_t *get_sys_status()
{
	return &my_sys_status;
}
//----------------------------------------------------------------------------------------------------------------
control_t *get_control()
{
  return &my_sys_status.s_control;
}
//----------------------------------------------------------------------------------------------------------------
uint8_t get_sys_alarm()
{
  return my_sys_status.s_alarm;
}
//get encoder, retorna o valor da posição do encoder
//----------------------------------------------------------------------------------------------------------------
uint16_t get_control_anguloEncoder()
{
  return my_sys_status.s_control.c_angulo_encoder;
}
//get modo de operação, retorna um char para IHM simbolizar qual é o modo de operação 
//----------------------------------------------------------------------------------------------------------------
char get_sys_modOperacaoIHM()
{
  if(my_sys_status.s_modo_de_oper == MODO_OPERACAO_VOLUME) 
    {
      return 'V';
    }
    else if(my_sys_status.s_modo_de_oper == MODO_OPERACAO_PRESSAO)
    {
      return 'P';
    }
}
//set função para mudar o modo de operação, no momento tempos volume e pressão
//----------------------------------------------------------------------------------------------------------------
void *set_sys_modOperacao(uint8_t modo)
{
  my_sys_status.s_modo_de_oper = modo;
}
//----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------
void *set_control_angulo(uint16_t volume_ihm) 
{
   float angulo = -1.85*volume_ihm + 3451;
   if(angulo < POSICAO_INF_LIMITE) angulo = POSICAO_INF_LIMITE;
   my_sys_status.s_control.c_angulo_final = (uint16_t) angulo;
}
//----------------------------------------------------------------------------------------------------------------
void *set_control_PEEP(uint8_t peep)
{
  if(L_PEEP_SUP < peep)
  {
    my_sys_status.s_control.c_pressao_PEEP = L_PEEP_SUP;
  }
  else if(L_PEEP_INF > peep)
  {
    my_sys_status.s_control.c_pressao_PEEP = L_PEEP_INF;
  }
  else
  {
     my_sys_status.s_control.c_pressao_PEEP = peep;
  }
}
//----------------------------------------------------------------------------------------------------------------
void *set_control_tempoInspiratorioIHM(uint16_t tempo_insp)
{
  if(L_TEMP_INSP_SUP < tempo_insp)
  {
    my_sys_status.s_control.c_tempo_insp_IHM = L_TEMP_INSP_SUP;
  }
  else if(L_TEMP_INSP_INF > tempo_insp)
  {
     my_sys_status.s_control.c_tempo_insp_IHM = L_TEMP_INSP_INF;
  }
  else
  {
    my_sys_status.s_control.c_tempo_insp_IHM = tempo_insp;
  }
}
//----------------------------------------------------------------------------------------------------------------
void *set_control_tempoExpiratorioIHM(uint8_t proporcao) //  proporcao seria 10 (1,0), 15 (1,5)
{                                                        //
  float provisorio;
  provisorio = my_sys_status.s_control.c_tempo_insp_IHM * proporcao / 10 - 550;
  
  if(provisorio < 0) provisorio = 0;
    my_sys_status.s_control.c_tempo_exp_ocioso = provisorio;
}
//----------------------------------------------------------------------------------------------------------------
void *set_control_pause(uint16_t delay)
{
  if(L_PAUSE_EXP_SUP < delay)
  {
    my_sys_status.s_control.c_tempo_exp_pause = L_PAUSE_EXP_SUP;
  }
  else if(L_PAUSE_EXP_INF > delay)
  {
    my_sys_status.s_control.c_tempo_exp_pause = L_PAUSE_EXP_INF;
  }
  else
  {
    my_sys_status.s_control.c_tempo_exp_pause = delay;
  }
}
//----------------------------------------------------------------------------------------------------------------
void *set_control_pressao(uint8_t pressao_ihm)
{
  if(L_PRESSAO_SUP < pressao_ihm)
  {
    my_sys_status.s_control.c_pressao_cont = L_PRESSAO_SUP;
  }
  else if(L_PRESSAO_INF > pressao_ihm)
  {
    my_sys_status.s_control.c_pressao_cont = L_PRESSAO_INF;
  }
  else
  {
    my_sys_status.s_control.c_pressao_cont = pressao_ihm;
  }
}
//----------------------------------------------------------------------------------------------------------------
void sys_status_Init()
{
  memset(&my_sys_status, 0, sizeof(system_status_t));

    //pré definições
    my_sys_status->s_modo_de_oper = MODO_OPERACAO_PRESSAO;
    
    my_sys_status->s_control.c_angulo_inicial = POSICAO_SUP_LIMITE;
    my_sys_status->s_control.c_angulo_final = 800;

    my_sys_status->s_control.c_pressao_PEEP = 10;
      
    my_sys_status->s_control.c_tempo_exp_pause = 400;//350~550
    my_sys_status->s_control.c_tempo_exp_ocioso = 1300;
    my_sys_status->s_control.c_tempo_insp_IHM  = 900;
    
    my_sys_status->s_control.c_pwm_insp = 200;
    //chute colocado na gaveta
    // my_sys_status->s_control.c_pwm_insp = palpite(my_sys_status->s_control.c_tempo_insp_IHM,
    //                                              my_sys_status->s_control.c_angulo_inicial,
    //                                              my_sys_status->s_control.c_angulo_final);
                                                 
    my_sys_status->s_control.c_pwm_requerido = my_sys_status->s_control.c_pwm_insp;
    
    my_sys_status->s_control.c_tempo_exp_ocioso = 550;
    my_sys_status->s_control.c_tempo_exp_pause = 350;
    my_sys_status->s_control.c_pressao_cont = 25;
    
  //limpando memória da struct
}
