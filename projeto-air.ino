#include "bibliotecas.h"

void desliga()
{
  set_sys_status(0);
  stop_Motor();
}
void setup() 
{
  button_Init();
  motor_Init();
  screen_Init();
  interrupt4_OVF_Init();
  control_init();

  set_sys_status(1);//inicializa controle
  Serial.begin(115200);
  pinMode(P_VALVULA_PRESSAO_EXP, INPUT);
  attachInterrupt(digitalPinToInterrupt(P_VALVULA_PRESSAO_EXP), desliga, FALLING);
}

void loop() 
{
  system_status * p_sys_status;
  p_sys_status = get_sys_status();

  Serial.print(" encoder: ");
  Serial.print(p_sys_status->s_control.c_encoder);
  Serial.print("\t tempo insp: ");
  Serial.print(p_sys_status->s_control.c_tempo_insp);
  Serial.print("\t tempo exp: ");
  Serial.print(p_sys_status->s_control.c_tempo_exp);
  Serial.print("\t pwm: ");
  Serial.println(p_sys_status->s_control.c_pwm_atual);

  //Serial.println( analogRead(P_SENSOR_PRESSAO));
 
}
