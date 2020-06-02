#include "bibliotecas.h"

void setup() {
  button_Init();
  motor_Init();
  screen_Init();
  interrupt4_OVF_Init();
  Serial.begin(9600);
  control_init();
}

void loop() {
  machine_state();
  //Serial.print();
  
}
