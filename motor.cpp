#include "bibliotecas.h"

void stop_Motor()
{                            
  digitalWrite(DRIVE_EN_L, LOW);
  digitalWrite(DRIVE_EN_R, LOW);
  OCR1A = 0;
  OCR1B = 0;
} 

void direct_Motor(uint8_t p, uint8_t duty)                                                    
{
  
  if(p==D_ROTACAO_0_DESCIDA)                                                
  {
    OCR1B = 0;
    OCR1A = duty;
    digitalWrite(DRIVE_EN_R, HIGH);                                             
    digitalWrite(DRIVE_EN_L, HIGH);
  }
  else if(p==D_ROTACAO_1_SUBIDA)
  { 
    OCR1A = 0;
    OCR1B = duty;
    digitalWrite(DRIVE_EN_R, HIGH);                                             
    digitalWrite(DRIVE_EN_L, HIGH);
  }
} 

void motor_Init()
{
  TCCR1A = 0b10101001; 
  TCCR1B = 0b00001010; 

  pinMode(DRIVE_PWM_R, OUTPUT);
  
  pinMode(DRIVE_PWM_L, OUTPUT);
  pinMode(DRIVE_EN_R, OUTPUT);
  pinMode(DRIVE_EN_L, OUTPUT);

  
  digitalWrite(DRIVE_EN_L, HIGH);
  digitalWrite(DRIVE_EN_R, HIGH);
}                                                                            
