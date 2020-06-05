#include "bibliotecas.h"

void setup() {
  button_Init();
  motor_Init();
  //screen_Init();
  interrupt4_OVF_Init();
  Serial.begin(115200);
  control_init();
  set_sys_status(1);
  system_status * p_sys_status;
  p_sys_status = get_sys_status();
  
}

void loop() {
  //machine_state();
  system_status * p_sys_status;
  p_sys_status = get_sys_status();
  Serial.print("Tempo: ");
  Serial.println(p_sys_status->s_control.c_tempo_insp);
 
}
