#include "bibliotecas.h"
//12/06


int tempo = millis();
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

  //set_sys_status(1);//inicializa controle
  
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
  //serial();
}
