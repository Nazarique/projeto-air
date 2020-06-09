#include "bibliotecas.h"

void desliga()
{
  set_sys_status(0);
  stop_Motor();
}
void setup() 
{
  //button_Init();
  motor_Init();
  //screen_Init();
  interrupt4_OVF_Init();
  control_init();

  set_sys_status(1);
  Serial.begin(115200);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), desliga, FALLING);
}

void loop() 
{
  //machine_state();
  system_status * p_sys_status;
  p_sys_status = get_sys_status();

  Serial.print("Tempo: ");
  Serial.println(p_sys_status->s_control.c_tempo_insp); 
}
