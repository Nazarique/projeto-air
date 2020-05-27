#include "bibliotecas.h"

void setup() {
  
  encoder_Init();
  button_Init();
  motor_Init();
  screen_Init();
  interrupt4_OVF_Init();
  Serial.begin(9600);
  
}

void loop() {
  machine_state();
  Serial.println(read_Posicao());
}
