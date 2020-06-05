#include "bibliotecas.h"

AS5045 encoder(AS_SPI_SS, AS_SPI_SCK, AS_SPI_MISO);
volatile uint8_t deadTime_Motor, degrau_Motor = 0;

tipoFuncao_p PonteiroDeFuncao;

void deadTimeMotor_Isr()                                                      
{
  /* Contadores usados para controle do motor, cont200 = 200ms, cont5 = 5ms.*/

  static uint8_t cont200 = 30;
  static uint8_t cont5 = 5;

  if(deadTime_Motor)                                                        
  {
    if(--cont200==0)                                                           
    { 
      cont200 = 30;                                                            
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
  uint8_t passo = 10;

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

void set_Degrau(control_t *motor)
{
  /* Função que verifica se teve um deadTime, após a verificação ela aciona
      o motor na posição definida. */
  if(degrau_Motor==0 && deadTime_Motor==0)
  {
    motor->c_pwm_atual = degrau(motor->c_pwm_requerido, 
                              motor->c_pwm_atual);
    degrau_Motor = 1;
    direct_Motor(motor->c_direcao, motor->c_pwm_atual);
  }
}

void maqEstados_Control()
{
  system_status * p_sys_status;
  p_sys_status = get_sys_status();

  if(p_sys_status->s_respirador)
  {
    PonteiroDeFuncao(p_sys_status);
  }
}

void control_Inspiracao(system_status *p_sys_status)
{
  /* Maq. de Estados: Inspiração
      função para execução dos procedimentos durante a fase
      se inspiração.
  */
  uint16_t posicao_encoder;

  posicao_encoder = ((uint16_t)(encoder.read()*0.08789));

  digitalWrite(P_VALVULA_PRESSAO_EXP, HIGH);
  p_sys_status->s_control.c_tempo_insp++;
  
  if (posicao_encoder > (p_sys_status->s_control.c_angulo_final))
  { 
    p_sys_status->s_control.c_direcao = 0;
    p_sys_status->s_control.c_pwm_requerido = 250;
    p_sys_status->s_control.c_pwm_atual = 0; 
    stop_Motor();        

    deadTime_Motor = 1;
    PonteiroDeFuncao = control_Expiracao;
    p_sys_status->s_control.c_tempo_insp = 0;
  }
  
  set_Degrau(&p_sys_status->s_control);
}

void control_Expiracao(system_status *p_sys_status)
{
  /* Maq. de Estados: Expiração
      função para execução dos procedimentos durante a fase
      se expiração.
  */
  
  uint16_t posicao_encoder;
  posicao_encoder = ((uint16_t)(encoder.read()*0.08789));
  
  if(analogRead(P_SENSOR_PRESSAO) < p_sys_status->s_control.c_pressao_PEEP)
  {
    digitalWrite(P_VALVULA_PRESSAO_EXP, HIGH);
  }
  else
  {
    digitalWrite(P_VALVULA_PRESSAO_EXP, LOW); 
  }

  if(posicao_encoder < (p_sys_status->s_control.c_angulo_inicial))
  { 
    p_sys_status->s_control.c_direcao = 1;
    p_sys_status->s_control.c_pwm_requerido = p_sys_status->s_control.c_pwm_insp;
    p_sys_status->s_control.c_pwm_atual= 0;
    stop_Motor();        

    deadTime_Motor = 1;
    PonteiroDeFuncao = control_Inspiracao;
  }
  set_Degrau(&p_sys_status->s_control);
}

void control_init()
{
  system_status * p_sys_status;  
  p_sys_status = get_sys_status();

  pinMode(P_VALVULA_PRESSAO_EXP, OUTPUT);
  encoder.begin();
  
  p_sys_status->s_control.c_angulo_inicial = 60;
  p_sys_status->s_control.c_angulo_final = 120;
  p_sys_status->s_control.c_pressao_PEEP = 6;

  p_sys_status->s_control.c_pwm_insp = 120;
  p_sys_status->s_control.c_pwm_requerido = p_sys_status->s_control.c_pwm_insp;
  PonteiroDeFuncao = control_Inspiracao;
}
