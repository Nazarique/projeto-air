#include "bibliotecas.h"

void stop_Motor()
{           
  digitalWrite(DRIVE_EN, LOW);                       

} 

void direct_Motor(uint8_t p, uint8_t duty)                                                    
{
  digitalWrite(DRIVE_EN, HIGH);
  if(p==D_ROTACAO_0_DESCIDA)                                                
  {
    OCR1A = duty;
    OCR1B = 0;                                                 
  }
  else if(p==D_ROTACAO_1_SUBIDA)
  {                                                                    
    OCR1A = 0;
    OCR1B = duty;
  }
} 

void motor_Init()
{
  TCCR1A = 0b10100001; 
  TCCR1B = 0b00001010; 

  pinMode(DRIVE_PWM_R, OUTPUT);
  pinMode(DRIVE_PWM_L, OUTPUT);
  pinMode(DRIVE_EN, OUTPUT);

  digitalWrite(DRIVE_EN, HIGH);  
}                                                                            
