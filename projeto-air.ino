#include "bibliotecas.h"
//12/06

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

  set_sys_status(1);//inicializa controle
  
  pinMode(S_SENSOR_INDUTIVO, INPUT);
  attachInterrupt(digitalPinToInterrupt(S_SENSOR_INDUTIVO), desliga, FALLING);


  pinMode(23,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(29,OUTPUT);

  //digitalWrite(23,HIGH);
  //digitalWrite(25,HIGH);
  digitalWrite(27,HIGH);
  //digitalWrite(29,HIGH);
}

void loop() 
{
  machine_state();
  system_status * p_sys_status;
  p_sys_status = get_sys_status();

  Serial.print(" encoder: ");
  Serial.print(p_sys_status->s_control.c_encoder);
  Serial.print("\t tempo insp: ");
  Serial.print(p_sys_status->s_control.c_tempo_insp);
  Serial.print("\t tempo exp: ");
  Serial.print(p_sys_status->s_control.c_tempo_exp);
  Serial.print("\t palpite pwm: ");
  Serial.print(palpite(p_sys_status->s_control.c_tempo_insp_IHM,
                       p_sys_status->s_control.c_angulo_inicial,
                       p_sys_status->s_control.c_angulo_final));
  Serial.print("\t pwm: ");
  Serial.println(p_sys_status->s_control.c_pwm_atual);
  
}
