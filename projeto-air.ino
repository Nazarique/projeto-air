#include "bibliotecas.h"

system_timer timer_ihm;
system_timer timer_serial_alarmes;

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
  
  pinMode(S_SENSOR_INDUTIVO, INPUT);
  attachInterrupt(digitalPinToInterrupt(S_SENSOR_INDUTIVO), desliga, LOW);

  timer_set(&timer_ihm, 10);
  timer_set(&timer_serial_alarmes, 300);
}
//----------------------------------------------------------------------------------------------------------------       
void loop() 
{
// static control_t *cont;
// cont = get_control();

  if (flag_control_stat_machine)
  {
    maqEstados_Control();
    flag_control_stat_machine = 0;
  }

  if(timer_expired(&timer_serial_alarmes))
  {
    serial();
    alarmes();
    timer_reset(&timer_serial_alarmes);
  }

 if(timer_expired(&timer_ihm))
 {
    machine_state();
    timer_reset(&timer_ihm);
 }
// Serial.println((int16_t)(cont->c_tempo_insp_IHM - cont->c_tempo_insp_cont))

}
