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
  Serial.print("DRIVE_IN2:  ");
  Serial.println(digitalRead(DRIVE_IN2));
  Serial.println(" ");
  Serial.print("pwm:  ");
  Serial.println(OCR1A);
  //machine_state();
  delay(400);
}
