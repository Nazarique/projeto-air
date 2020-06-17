#include "bibliotecas.h"

AS5045 encoder(AS_SPI_SS, AS_SPI_SCK, AS_SPI_MISO);

tipoFuncao_p PonteiroDeFuncao;
/* Ponteiro de função é usado para fzer a troca de estados, para 
    o controle via interrupção.*/

uint8_t rampa(uint8_t pwm, uint8_t pwm_atual)
{
  /* Função que compara o valor atual do PWM, a realiza o rampa para o
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

void set_rampa(control_t *motor)
{
  /* Função que verifica se houve um deadTime, após a verificação ela aciona
      o motor na posição definida. */
  /* Contadores usados para controle do motor, cont200 = 200ms, cont5 = 5ms.*/

  static uint16_t cont35 = 350;
  static uint16_t cont_exp = motor->c_tempo_exp_ocioso;
  static uint8_t cont5 = 5;
  static uint8_t rampa_Motor = 0;

  if(motor->c_deadTime_Motor)                                                        
  {
    if(--cont35==0)                                                           
    { 
      cont35 = 350;                                                            
      motor->c_deadTime_Motor = 0; 
    }
  }

  else if(motor->c_flag_exp_ocioso)                                                        
  {
    if(--cont_exp==0)                                                           
    { 
      cont_exp = motor->c_tempo_exp_ocioso;                                                            
      motor->c_flag_exp_ocioso = 0; 
    }
  }

  else if(rampa_Motor)
  {
    if(--cont5==0)                                                           
    { 
      cont5 = 5;                                            
      rampa_Motor = 0;                                                                                                              
    }
  }

  else if(!rampa_Motor)
  {
    motor->c_pwm_atual = rampa(motor->c_pwm_requerido, 
                                motor->c_pwm_atual);
    rampa_Motor = 1;
    direct_Motor(motor->c_direcao, motor->c_pwm_atual);
  }
}

void maqEstados_Control()
{
  /* Maquina de estados para controle de inspração e expiração, uma 
      struct para armazenamento de variaveis é usado, para criar um link
      entre o controle e as alterações que podem ser feitas via IHM.*/

  system_status_t * p_sys_status;
  p_sys_status = get_sys_status();

  if(p_sys_status->s_respirador)
  {
    PonteiroDeFuncao(p_sys_status);
  }
}

void control_Inspiracao(system_status_t *p_sys_status)
{
  /* Maq. de Estados: Inspiração
      função para execução dos procedimentos durante a fase
      de inspiração.
  */
  uint16_t posicao_encoder;
  static uint32_t cont_time = 0;
  
  posicao_encoder = encoder.read();
  p_sys_status->s_control.c_angulo_encoder = posicao_encoder;
  
  cont_time++;
  
  if (posicao_encoder < (p_sys_status->s_control.c_angulo_final) &&  posicao_encoder > 200)
  { 
    p_sys_status->s_control.c_deadTime_Motor = 1;
    p_sys_status->s_control.c_pwm_requerido  = 250;
    p_sys_status->s_control.c_pwm_atual      = 0; 
    p_sys_status->s_control.c_flag_exp_ocioso       = 1;
    p_sys_status->s_control.c_direcao        = 0;
    p_sys_status->s_control.c_tempo_insp_cont = cont_time;
    cont_time = 0;
    stop_Motor();       
    PonteiroDeFuncao = control_Expiracao;
  }
  set_rampa(&p_sys_status->s_control);
}

void control_Expiracao(system_status_t *p_sys_status)
{
  /* Maq. de Estados: Expiração
      função para execução dos procedimentos durante a fase
      de expiração.
  */
  static uint32_t cont_time = 0;
  
  uint16_t posicao_encoder;
  posicao_encoder = encoder.read();
  
  p_sys_status->s_control.c_angulo_encoder = posicao_encoder;
  cont_time++;
  if(/*((uint8_t)((analogRead(P_SENSOR_PRESSAO)-48)*0.1105) > p_sys_status->s_control.c_pressao_PEEP) && */cont_time > p_sys_status->s_control.c_tempo_exp_pause)
  {
    digitalWrite(P_VALVULA_PRESSAO_EXP, HIGH);
  }
//  else
//  {
//    digitalWrite(P_VALVULA_PRESSAO_EXP, LOW); 
//  }
  
  if(posicao_encoder > (p_sys_status->s_control.c_angulo_inicial) || posicao_encoder < 200)
  { 
    p_sys_status->s_control.c_deadTime_Motor = 1;
    p_sys_status->s_control.c_pwm_atual      = 0;
    p_sys_status->s_control.c_direcao        = 1;
    p_sys_status->s_control.c_tempo_exp_cont = cont_time;
    
    if(p_sys_status->s_control.c_tempo_insp_cont != 0)
    {
      p_sys_status->s_control.c_pwm_insp = compensador(p_sys_status->s_control.c_tempo_insp_IHM,
                                                       p_sys_status->s_control.c_tempo_insp_cont, 
                                                       p_sys_status->s_control.c_pwm_insp);
    }                                                       
                                                          
    p_sys_status->s_control.c_pwm_requerido = p_sys_status->s_control.c_pwm_insp;
    cont_time = 0;
    stop_Motor();   

    PonteiroDeFuncao = control_Inspiracao;
    digitalWrite(P_VALVULA_PRESSAO_EXP, LOW);
  }
  set_rampa(&p_sys_status->s_control);
}

uint8_t compensador(uint16_t tempo_inspiratorio_IHM,
                    uint16_t tempo_inspiratorio, uint8_t pwm_atual)
{
  int erro = 0;
  float kp = -0.1;
  uint16_t pwm = 0;

  erro = tempo_inspiratorio_IHM - tempo_inspiratorio;
    
  pwm = pwm_atual + (kp*erro) + 1;

  if(pwm > 250)
  {
    pwm = 250;
  } 
  else if(pwm < 40)
  {
    pwm = 40;
  }
  
   return (uint8_t)pwm; 
}

uint8_t palpite(uint16_t tempo_inspiratorio_IHM, uint16_t angulo_init, uint16_t angulo_final){

  float p00 =  3132;
  float p10 =  56.19;
  float p01 = -65.79;
  float p11 = -0.5411;
  float p02 =  0.4963;
  float p12 =  0.001415;
  float p03 = -0.001128;
  
  //tempo_inspiratorio_IHM *= 1000; //isso é porque na IHM não usa ms e sim s
  float volume = (angulo_init - angulo_final)*0.08789;
  float a = 250;
  float b = 40;
  float resultado = 100;
  float pwm_raiz = 0;
  
  while(abs(resultado) > 2){
    pwm_raiz = (a+b)/2;

    resultado = - ((float)tempo_inspiratorio_IHM)
                + (p00) 
                + (p10 * volume)
                + (p01 * pwm_raiz)
                + (p11 * volume * pwm_raiz)
                + (p02 * pow(pwm_raiz, 2))
                + (p12 * volume * pow(pwm_raiz, 2))
                + (p03 * pow(pwm_raiz, 3));    
    if(resultado>0){
      b=pwm_raiz;
    }else{
      a=pwm_raiz;
    }
  }
  return (uint8_t)pwm_raiz;
}                

void control_init()
{
  /* Função responsavél de iniciar parametros de controle, como PWM,
      posição final e inicial.*/

  system_status_t * p_sys_status;  
  p_sys_status = get_sys_status();

  pinMode(P_VALVULA_PRESSAO_EXP, OUTPUT);
  encoder.begin();
  //pré definições
  //-*
  p_sys_status->s_control.c_angulo_inicial  = 3900;
  p_sys_status->s_control.c_angulo_final    = 3100;

  p_sys_status->s_control.c_pressao_PEEP    = 3;
    
  p_sys_status->s_control.c_tempo_exp_pause = 400;//350~550
  p_sys_status->s_control.c_tempo_exp_ocioso = 1100;
  p_sys_status->s_control.c_tempo_insp_IHM  = 900;
  
  p_sys_status->s_control.c_pwm_insp = palpite(p_sys_status->s_control.c_tempo_insp_IHM,
                                               p_sys_status->s_control.c_angulo_inicial,
                                               p_sys_status->s_control.c_angulo_final);
                                               
  p_sys_status->s_control.c_pwm_requerido = p_sys_status->s_control.c_pwm_insp;
  
  p_sys_status->s_control.c_tempo_exp_ocioso = 550;
  p_sys_status->s_control.c_tempo_exp_pause = 350;
  p_sys_status->s_control.c_pressao_cont = 15;

  //-*
  PonteiroDeFuncao = control_Expiracao;
}
