#include "bibliotecas.h"

AS5045 encoder(AS_SPI_SS, AS_SPI_SCK, AS_SPI_MISO);

<<<<<<< HEAD
static motorAux_t motor = {0};
static posicao_t posi = {0};

void deadTimeMotor_Isr()                                                      
{
  /* Contadores usados para controle do motor, cont20 = 20ms, cont5 = 5ms.*/

  static uint8_t cont300 = 300;
  static unsigned char cont5 = 5;

  if(deadTime_Motor)                                                        
  {
    if(--cont300==0)                                                           
    { 
      cont300 = 300;                                                            
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
=======
tipoFuncao_p PonteiroDeFuncao;
/* Ponteiro de função é usado para fzer a troca de estados, para 
    o controle via interrupção.*/
>>>>>>> remotes/origin/deadTime_Control

uint8_t degrau(uint8_t pwm, uint8_t pwm_atual)
{
  /* Função que compara o valor atual do PWM, a realiza o degrau para o
      PWM desejado.*/

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
  /* Função que verifica se houve um deadTime, após a verificação ela aciona
      o motor na posição definida. */
  /* Contadores usados para controle do motor, cont200 = 200ms, cont5 = 5ms.*/

  static uint16_t cont35 = 350;
  static uint16_t cont_exp = 100;
  static uint8_t cont5 = 5;
  static uint8_t degrau_Motor = 0;

  if(motor->c_deadTime_Motor)                                                        
  {
    if(--cont35==0)                                                           
    { 
      cont35 = 350;                                                            
      motor->c_deadTime_Motor = 0; 
    }
  }

  else if(motor->c_cont_exp)                                                        
  {
    if(--cont_exp==0)                                                           
    { 
      cont_exp = motor->c_tempo_exp_teste;                                                            
      motor->c_cont_exp = 0; 
    }
  }

  else if(degrau_Motor)
  {
    if(--cont5==0)                                                           
    { 
      cont5 = 5;                                            
      degrau_Motor = 0;                                                                                                              
    }
  }

  else if(!degrau_Motor)
  {
    motor->c_pwm_atual = degrau(motor->c_pwm_requerido, 
                                motor->c_pwm_atual);
    degrau_Motor = 1;
    direct_Motor(motor->c_direcao, motor->c_pwm_atual);
  }
}

void maqEstados_Control()
{
  /* Maquina de estados para controle de inspração e expiração, uma 
      struct para armazenamento de variaveis é usado, para criar um link
      entre o controle e as alterações que podem ser feitas via IHM.*/

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
      de inspiração.
  */
  uint16_t posicao_encoder;
  static uint32_t cont_time = 0;
  
  posicao_encoder = encoder.read();
  
  p_sys_status->s_control.c_encoder = posicao_encoder;
  
  cont_time++;
  
  digitalWrite(P_VALVULA_PRESSAO_EXP, HIGH);
  
  if (posicao_encoder < (p_sys_status->s_control.c_angulo_final) &  posicao_encoder > 200)
  { 
    p_sys_status->s_control.c_direcao = 0;
    p_sys_status->s_control.c_pwm_requerido = 250;
    p_sys_status->s_control.c_pwm_atual = 0; 
    p_sys_status->s_control.c_deadTime_Motor = 1;
    p_sys_status->s_control.c_cont_exp = 1;
    p_sys_status->s_control.c_tempo_insp = cont_time;
    cont_time = 0;
    stop_Motor();       
     
    PonteiroDeFuncao = control_Expiracao;
  }
  set_Degrau(&p_sys_status->s_control);
}

void control_Expiracao(system_status *p_sys_status)
{
  /* Maq. de Estados: Expiração
      função para execução dos procedimentos durante a fase
      de expiração.
  */
  static uint32_t cont_time = 0;
  
  uint16_t posicao_encoder;
  posicao_encoder = encoder.read();
  
  p_sys_status->s_control.c_encoder = posicao_encoder;
  
  cont_time++;
  if(analogRead(P_SENSOR_PRESSAO) < p_sys_status->s_control.c_pressao_PEEP)
  {
    digitalWrite(P_VALVULA_PRESSAO_EXP, HIGH);
  }
  else
  {
    digitalWrite(P_VALVULA_PRESSAO_EXP, LOW); 
  }
  
  if(posicao_encoder > (p_sys_status->s_control.c_angulo_inicial)|posicao_encoder < 200)
  { 
    p_sys_status->s_control.c_direcao = 1;
    p_sys_status->s_control.c_pwm_requerido = p_sys_status->s_control.c_pwm_insp;
    p_sys_status->s_control.c_pwm_atual= 0;
    p_sys_status->s_control.c_deadTime_Motor = 1;
    p_sys_status->s_control.c_tempo_exp = cont_time;
    cont_time = 0;
    stop_Motor();   
    
  }
  set_Degrau(&p_sys_status->s_control);
}

void control_init()
{
  /* Função responsavél de iniciar parametros de controle, como PWM,
      posição final e inicial.*/

  system_status * p_sys_status;  
  p_sys_status = get_sys_status();

  pinMode(P_VALVULA_PRESSAO_EXP, OUTPUT);
  encoder.begin();
  
  p_sys_status->s_control.c_angulo_inicial = 4000;
  p_sys_status->s_control.c_angulo_final = 3100;
  p_sys_status->s_control.c_pressao_PEEP = 6;
  p_sys_status->s_control.c_pwm_insp = 150;
  p_sys_status->s_control.c_pwm_requerido = p_sys_status->s_control.c_pwm_insp;
  p_sys_status->s_control.c_tempo_exp_teste = 150;

  PonteiroDeFuncao = control_Expiracao;
}
