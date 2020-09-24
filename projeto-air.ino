#include "bibliotecas.h"

void desliga()
{
  static uint16_t cont_ind = 1000;
  
  if(--cont_ind==0){
    set_sys_status(0);
    stop_Motor();
    cont_ind = 1000;
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
  
  pinMode(S_SENSOR_INDUTIVO, INPUT);
  attachInterrupt(digitalPinToInterrupt(S_SENSOR_INDUTIVO), desliga, LOW);
}
//----------------------------------------------------------------------------------------------------------------       
void loop() 
{
 static control_t *s_cont;
 cont = get_control();

 machine_state();
 Serial.println((int16_t)(cont->c_tempo_insp_IHM - cont->c_tempo_insp_cont))
}
