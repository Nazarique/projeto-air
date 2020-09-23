#include "bibliotecas.h"

AS5045 encoder(AS_SPI_SS, AS_SPI_SCK, AS_SPI_MISO);

static bool flag_peep = 1;

tipoFuncao_p PonteiroDeFuncao;
/* Ponteiro de função é usado para fzer a troca de estados, para 
    o controle via interrupção.*/
//
//
//
// Rampa
//
//
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
//
//
//
// Contadores/set Rampa
//
//
//----------------------------------------------------------------------------------------------------------------
void set_rampa(control_t *motor)
{
  /* Função que verifica se houve um deadTime, após a verificação ela aciona
      o motor na posição definida.
    Contadores usados para controle do motor, contador para dead time, 
      rampa e tempo ocioso, o tempo ocioso é o tempo em que de troca de inpiração
      para expiração. */

  static uint16_t cont35 = 350;
  static uint16_t cont_exp = motor->c_tempo_exp_ocioso;
  static uint8_t cont5 = 5;
  static uint8_t rampa_Motor = 0;

//Contador dead time para motor 
//Este contador mantém o motor desligado na troca de rotação
  if(motor->c_deadTime_Motor)
  {
    if(--cont35==0)                                                           
    { 
      cont35 = 350;                                                            
      motor->c_deadTime_Motor = 0; 
    }
  }
//Contador para expiração
//Este contador mantém a válvula de expiração fechada pelo tempo solicitado   
  else if(motor->c_flag_exp_ocioso)                                                        
  {
    if(--cont_exp==0)                                                           
    { 
      cont_exp = motor->c_tempo_exp_ocioso;   //set tempo ocioso após a sua primeira contagem                                                         
      motor->c_flag_exp_ocioso = 0; 
    }
  }
//Contador rampa de PWM
//Este contador incrementa conta o intervalo de tempo para o incremento da rampa para o PWM
  else if(rampa_Motor)
  {
    if(--cont5==0)                                                           
    { 
      cont5 = 5;                                            
      rampa_Motor = 0;                                                                                                              
    }
  }
//Set rampa
/*  Após a verificação do contador de incremento para rampa, há um aumento no valor do PWM
      até eu valor alcançar o valor requerito */ 
  else if(!rampa_Motor)
  {
    motor->c_pwm_atual = rampa(motor->c_pwm_requerido, 
                                motor->c_pwm_atual);
    rampa_Motor = 1;
    direct_Motor(motor->c_direcao, motor->c_pwm_atual);
  }
}
//
//
//
// maq. de estados de controle
//
//
//----------------------------------------------------------------------------------------------------------------
void maqEstados_Control()
{
  /* Maquina de estados para controle de inspração e expiração, uma 
      struct para armazenamento de variaveis é usado, para criar um link
      entre o controle e as alterações que podem ser feitas via IHM.*/

  system_status_t * p_sys_status;
  p_sys_status = get_sys_status();

// variável s_respirador é responsável em sinalizar se o sistema está ativo ou não
// s_respirador == 1, sistema ligado
// s_respirador == 0, sistema desligado 
  if(p_sys_status->s_respirador)
  {
    //maq. estados de controle...  
    PonteiroDeFuncao(p_sys_status);
  }
}

//
//
//
// Controle de inspiração no modo volume
//
//
//----------------------------------------------------------------------------------------------------------------
void control_Inspiracao_volume(system_status_t *p_sys_status)
{
  /* Maq. de Estados: Inspiração volume
      função para execução dos procedimentos durante a fase
      de inspiração no modo de volume.
  */
  //variável cont_time responsável por contar o tempo em que a função é exucutada
  static uint32_t cont_time = 0;
  //variável aux para armazenar a posição do encoder
  uint16_t posicao_encoder = 0;
  //variável aux para armazenar a pressão lida
  uint16_t aux_pressao_lida = ( (analogRead(P_SENSOR_PRESSAO) -48 ) * 0.1105 );
  
  posicao_encoder = encoder.read();
  
  p_sys_status->s_control.c_angulo_encoder = posicao_encoder;
  
  cont_time++;
  
/* teste de vazamento, quando sensor de pressão tem um valor proximo de 48, sabemos
    que sua leitura é a mesma da pressão ambiente, por este motivo, sempre que seu valor estiver dentro 
    da conição do IF sabemos que há algum vazemento */

  if(analogRead(P_SENSOR_PRESSAO) > 46 && analogRead(P_SENSOR_PRESSAO) < 50)
  {
    p_sys_status->s_alarm = ALARM_VAZAMENTO;
  } 
  else
  {
    p_sys_status->s_alarm = ALARM_LIGADO;
  }
  

/* No modo de operação via volume precisamos realizar uma troca entre inspiração e expiração
    de acordo com a posição do encoder, pois o delta de angulo do encoder, esta diretamente ligado ao 
    volume setado para inspiração do paciênte. Para melhor controle é usado um range no if. */  

   if(posicao_encoder < (p_sys_status->s_control.c_angulo_final) || aux_pressao_lida > L_PRESSAO_SUP)
  {
      if(aux_pressao_lida > 40){
          p_sys_status->s_alarm = ALARM_PRESSAO_ALTA;
      }
      else if(aux_pressao_lida < (p_sys_status->s_control.c_pressao_cont - 5)) {
          p_sys_status->s_alarm = ALARM_PRESSAO_BAIXA; 
      }
      else
      {
          p_sys_status->s_alarm = ALARM_LIGADO;
      }
    // o motor inverte rotação, assim usamos um dead time para inversão.  
    p_sys_status->s_control.c_deadTime_Motor = 1;
    p_sys_status->s_control.c_pwm_requerido  = 250;
    p_sys_status->s_control.c_pwm_atual      = 0; 
    p_sys_status->s_control.c_flag_exp_ocioso= 1;
    p_sys_status->s_control.c_direcao        = D_ROTACAO_0_SUBIDA;
    p_sys_status->s_control.c_tempo_insp_cont = cont_time;
    cont_time = 0;
    stop_Motor();       
    PonteiroDeFuncao = control_Expiracao;
  }
  //PWM subindo em rampa
  set_rampa(&p_sys_status->s_control);
}
//
//
//
// Controle de inspiração no modo pressão
//
//
//----------------------------------------------------------------------------------------------------------------
void control_Inspiracao_pressao(system_status_t *p_sys_status)
{
  /* Maq. de Estados: Inspiração pressão
      função para execução dos procedimentos durante a fase
      de inspiração no modo pressão.
  */
  //variável cont_time responsável por contar o tempo em que a função é exucutada
  static uint32_t cont_time = 0;
  //variável aux para armazenar a posição do encoder
  uint16_t posicao_encoder = 0;
  //variável aux para armazenar a pressão lida
  uint16_t aux_pressao_lida = ( (analogRead(P_SENSOR_PRESSAO) -48 ) * 0.1105 );
  
  posicao_encoder = encoder.read();
  
  p_sys_status->s_control.c_angulo_encoder = posicao_encoder;
  
  cont_time++;

/* teste de vazamento, quando sensor de pressão tem um valor proximo de 48, sabemos
    que sua leitura é a mesma da pressão ambiente, por este motivo, sempre que seu valor estiver dentro 
    da conição do IF sabemos que há algum vazemento */

  if(analogRead(P_SENSOR_PRESSAO) > 46 && analogRead(P_SENSOR_PRESSAO) < 50)
  {
    p_sys_status->s_alarm = ALARM_VAZAMENTO;
  } 
  else
  {
    p_sys_status->s_alarm = ALARM_LIGADO;
  }
  

/* No modo de operação via pressão precisamos realizar uma troca entre inspiração e expiração
    de acordo com a pressão que é lida no sensor de pressão, se a pressão real alcançar a pressão 
    estipulada para inspiração do paciênte ocorre a troca. Caso o encoder chegue na posição de 
    volume maxímo a troca também acontece. */

  if(aux_pressao_lida > p_sys_status->s_control.c_pressao_cont ||  posicao_encoder < POSICAO_INF_LIMITE) //2900 É A POSIÇÃO LIMITE NO MOMENTO
  { 
    //Caso o encoder chegue na posição de volume maxímo um alarme é acionado.
    if(posicao_encoder < POSICAO_SUP_LIMITE) p_sys_status->s_alarm = ALARM_VOLUME_MAX; //PRIORIDADE
    
    if(aux_pressao_lida > L_PRESSAO_SUP)
    {
      p_sys_status->s_alarm = ALARM_PRESSAO_ALTA;
    }
    else if(aux_pressao_lida < (p_sys_status->s_control.c_pressao_cont - 5)) 
    {
      p_sys_status->s_alarm = ALARM_PRESSAO_BAIXA; 
    }
    else
    {
      p_sys_status->s_alarm = ALARM_LIGADO;
    }
    // o motor inverte rotação, assim usamos um dead time para inversão. 
    p_sys_status->s_control.c_deadTime_Motor = 1;
    p_sys_status->s_control.c_pwm_requerido  = 250;
    p_sys_status->s_control.c_pwm_atual      = 0; 
    p_sys_status->s_control.c_flag_exp_ocioso= 1;
    p_sys_status->s_control.c_direcao        = D_ROTACAO_0_SUBIDA;//subir
    p_sys_status->s_control.c_tempo_insp_cont = cont_time;
    cont_time = 0;
    stop_Motor();       
    PonteiroDeFuncao = control_Expiracao;
  }
  //PWM subindo em rampa
  set_rampa(&p_sys_status->s_control);
}
//
//
//
// Controle de expiração
//
//
//----------------------------------------------------------------------------------------------------------------
void control_Expiracao(system_status_t *p_sys_status)
{
  /* Maq. de Estados: Expiração
      função para execução dos procedimentos durante a fase
      de expiração.
  */
  //variável cont_time responsável por contar o tempo em que a função é exucutada
  static uint32_t cont_time = 0;
  //variável aux para armazenar a posição do encoder
  uint16_t posicao_encoder = 0;
  //variável aux para armazenar a pressão lida
  uint16_t aux_pressao_lida = ( (analogRead(P_SENSOR_PRESSAO) -48 ) * 0.1105 );

  posicao_encoder = encoder.read();
  
  p_sys_status->s_control.c_angulo_encoder = posicao_encoder;
  cont_time++;

  //A condição do if verifica se o tempo de pausa expiratória ja foi contado
  //E deixa em ativo uma flag para manter a verificação da PEEP
  if(cont_time > p_sys_status->s_control.c_tempo_exp_pause && flag_peep)
  {
    //abriu válvula
    digitalWrite(P_VALVULA_PRESSAO_EXP, HIGH);
    flag_peep = 1;
  }
  //A condição do if verifica se a pressão atual é menor que a PEEP
  //Caso a pressão estiver menor, a válvula fecha para mantér a PEEP
  if(p_sys_status->s_control.c_pressao_PEEP > aux_pressao_lida && flag_peep){
    //fechou válvula
    flag_peep = 0;
    digitalWrite(P_VALVULA_PRESSAO_EXP, LOW);  
  }
  /* Caso a válvula esteja fechada por que ocorreu o if anterior, e mesmo assim a
       pressão é superior a PEEP estabelecida pela IHM, é porque ocorreu algum problema,
       sendo assim uma flag de alta PEEP é acionada*/

  else if( aux_pressao_lida > (5 + p_sys_status->s_control.c_pressao_PEEP)  && !flag_peep) //PRIORIDADE
  {
    p_sys_status->s_alarm =  ALARM_ALTA_PEEP;
  } 
  /* A troca entre expiração e inspiração acontece caso o encoder chegue na posição de inicial */

  if(posicao_encoder > (p_sys_status->s_control.c_angulo_inicial))
  { 
    // o motor inverte rotação, assim usamos um dead time para inversão. 
    p_sys_status->s_control.c_deadTime_Motor = 1;
    p_sys_status->s_control.c_pwm_atual      = 0;
    p_sys_status->s_control.c_direcao        = D_ROTACAO_1_DESCIDA;
    p_sys_status->s_control.c_tempo_exp_cont = cont_time;

    //se o tempo de inspiração anterior for diferente de zero
    //um compensador é usado para setar o pwm requerido de acordo com o tempo de inspiração setado
    if(p_sys_status->s_control.c_tempo_insp_cont != 0)
    {
      p_sys_status->s_control.c_pwm_insp = compensador(p_sys_status->s_control.c_tempo_insp_IHM,
                                                       p_sys_status->s_control.c_tempo_insp_cont, 
                                                       p_sys_status->s_control.c_pwm_insp);
    }                                                       
    p_sys_status->s_control.c_pwm_requerido = p_sys_status->s_control.c_pwm_insp;

    cont_time = 0;
    stop_Motor(); 

    //fecha válvula para entrar na inspiração 
    digitalWrite(P_VALVULA_PRESSAO_EXP, LOW);
    flag_peep = 1;

    //se o modo de operação setando na IHM for volume a funçãode inspiração é alterada
    if(p_sys_status->s_modo_de_oper == MODO_OPERACAO_VOLUME) 
    {
      PonteiroDeFuncao = control_Inspiracao_volume;
    }
    //se o modo de operação setando na IHM for pressão a função de inspiração é alterada
    else if(p_sys_status->s_modo_de_oper == MODO_OPERACAO_PRESSAO)
    {
      PonteiroDeFuncao = control_Inspiracao_pressao;
    }  
  }
  //PWM subindo em rampa
  set_rampa(&p_sys_status->s_control);
}
//
//
//
// Compensador
//
//
//----------------------------------------------------------------------------------------------------------------
uint8_t compensador(uint16_t tempo_inspiratorio_IHM,
                    uint16_t tempo_inspiratorio, uint8_t pwm_atual)
{
  /*          
        (tempo de inspiração real)-----→(erro)------→(kp)------→(schefflera)-----→ PWM
                                        ↑----(tempo de inspiração real)----↓
    O compensador é usado para obter um pwm que se ajuste com o controle de 
    tempo de inspiração.
  */
  int16_t erro = 0;
  float kp = -0.12;
  uint8_t pwm = 0;

  erro = tempo_inspiratorio_IHM - tempo_inspiratorio;
    
  pwm = pwm_atual + (kp * erro) + 1;

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
//
//
//
// Palpite
//
//
//----------------------------------------------------------------------------------------------------------------
uint8_t palpite(uint16_t tempo_inspiratorio_IHM, uint16_t angulo_init, uint16_t angulo_final){
  /*Esta função usa uma equação polinomial de 3° grau para achar o valor mais proximo
      do PWM para ter um tempo de inspiração igual ao que foi iniciado, assim o controle via
      compensador realiza menos passos até chegar ao valor estipulado.  
  */
  float p00 =  3132.0;
  float p10 =  56.19;
  float p01 = -65.79;
  float p11 = -0.5411;
  float p02 =  0.4963;
  float p12 =  0.001415;
  float p03 = -0.001128;
  float volume = (angulo_init - angulo_final)*0.08789;
  float a = 250.0;
  float b = 40.0;
  float resultado = 100.0;
  float pwm_raiz = 0.0;
  
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

//
//
//
// control_init
//
//
//----------------------------------------------------------------------------------------------------------------
void control_init()
{
  /* Função responsavél de iniciar parametros de controle, como PWM,
      posição final e inicial.*/

  pinMode(P_VALVULA_PRESSAO_EXP, OUTPUT);
  encoder.begin();

  //ponteiro de função responsavel pela inversão na maquina de estado para controle
  PonteiroDeFuncao = control_Expiracao;
}
