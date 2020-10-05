#include "bibliotecas.h"

system_timer timer_ihm;
system_timer timer_serial_alarmes;

void alarmes(){

  uint8_t pwm_buzzer = 255;
  uint8_t var = get_sys_alarm();
  char mod = get_sys_modOperacaoIHM();
  switch(var) {
  
  case 0:
      digitalWrite(L_LED_VERDE, LOW);
      
   break;
  
  case 1:
      digitalWrite(L_LED_VERDE, HIGH);
      digitalWrite(L_LED_VERMELHO, LOW);
      digitalWrite(B_ALARM_BUZZER, 0);
    break;
  case 2:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
    break;

  case 3:
   break;
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
  case 4:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
   break;

  case 5:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
   break;

  case 6:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
   break;

  default:
      digitalWrite(L_LED_VERDE, HIGH);
      digitalWrite(L_LED_VERMELHO, LOW);
      digitalWrite(B_ALARM_BUZZER, 0);
    break;
  }
  switch(mod){
    case 'P':
      digitalWrite(L_LED_AZUL, HIGH);
      digitalWrite(L_LED_AMARELO, LOW);
      break;
   case 'V':
      digitalWrite(L_LED_AMARELO, HIGH);
      digitalWrite(L_LED_AZUL, LOW);
      break;
      
  }
}
//----------------------------------------------------------------------------------------------------------------       
void serial()
{  
  volatile data dado;
  memset(&dado, 0, sizeof(data));

  dado.alarm = get_sys_alarm();
  dado.angulo = get_control_anguloEncoder();
  dado.pressao = (int16_t)((analogRead(P_SENSOR_PRESSAO)- 48)*0.1105);
  
  const int capacity = JSON_OBJECT_SIZE(3);//nosso documento Json possui no 3 valores;  
  StaticJsonDocument<capacity> doc;
  
  doc["alarm"] = dado.alarm;
  doc["pressao"] = dado.pressao;
  doc["angulo"] = dado.angulo;
 
  serializeJson(doc, Serial);
  Serial.println(); 
  
}
void desliga()
{
  static uint16_t cont_ind = 5000;
  
  if(--cont_ind==0){
    set_sys_status(0);
    stop_Motor();
    cont_ind = 5000;
    Serial.println("sensor");
  }
}
//----------------------------------------------------------------------------------------------------------------       
void setup() 
{
  Serial.begin(115200);
  sys_status_Init();
  button_Init();
  motor_Init();
  screen_Init();
  interrupt4_OVF_Init();
  control_init();

  pinMode(L_LED_AMARELO, OUTPUT);
  pinMode(L_LED_AZUL, OUTPUT);
  pinMode(L_LED_VERDE, OUTPUT);
  pinMode(L_LED_VERMELHO, OUTPUT);
  
  digitalWrite(L_LED_AMARELO, HIGH);
  digitalWrite(L_LED_AZUL, HIGH);
  digitalWrite(L_LED_VERDE, HIGH);
  digitalWrite(L_LED_VERMELHO, HIGH);

  pinMode(B_ALARM_BUZZER, OUTPUT);
  pinMode(S_SENSOR_INDUTIVO, INPUT);
  
  //attachInterrupt(digitalPinToInterrupt(S_SENSOR_INDUTIVO), desliga, LOW);

  timer_set(&timer_ihm, T_PERIODO_IHM);
  timer_set(&timer_serial_alarmes, T_PERIODO_SERIAL_ALARM);
  //set_sys_status(1);
  
}
//----------------------------------------------------------------------------------------------------------------       
void loop() 
{
    if(flag_control_stat_machine)
    {
      maqEstados_Control();
      flag_control_stat_machine = 0;
    }
    /* Maquina de estado de controle, com o periodo de operação na faixa de 1ms, com contadores internos com precisão usando "watch_exp/insp"*/

 // if(timer_expired(&timer_serial_alarmes))
 // {
 //   //serial();
 //   timer_reset(&timer_serial_alarmes);
 // }
 // // Serial e alames, com o periodo de operação na faixa de 300ms
//
  if(timer_expired(&timer_ihm))
  {
     machine_state();
     //alarmes();
     timer_reset(&timer_ihm);
  }
 // Maquina de estado de IHM, com o periodo de operação na faixa de 50ms
}
