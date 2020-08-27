#include "bibliotecas.h"
//12/08


void desliga()
{
  set_sys_status(0);
  stop_Motor();
}

void setup() 
{
  
  Serial.begin(115200);

  button_Init();
  motor_Init();
  screen_Init();
  interrupt4_OVF_Init();
  control_init();
  
  pinMode(S_SENSOR_INDUTIVO, INPUT);
  //attachInterrupt(digitalPinToInterrupt(S_SENSOR_INDUTIVO), desliga, FALLING);

  
  pinMode(L_LED_AMARELO, OUTPUT);
  pinMode(L_LED_AZUL, OUTPUT);
  pinMode(L_LED_VERDE, OUTPUT);
  pinMode(L_LED_VERMELHO, OUTPUT);
  
  digitalWrite(L_LED_AMARELO, HIGH);
  digitalWrite(L_LED_AZUL, HIGH);
  digitalWrite(L_LED_VERDE, HIGH);
  digitalWrite(L_LED_VERMELHO, HIGH);

 // pinMode(B_ALARM_BUZZER, OUTPUT);
  
  uint8_t pwm_buzzer = 255;
  
  pinMode(B_ALARM_BUZZER, OUTPUT);
  //digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
  
}

void loop() 
{
 machine_state();

}
