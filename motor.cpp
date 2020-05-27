#include "bibliotecas.h"

void stop_Motor()
{                                  
  digitalWrite(DRIVE_IN1,LOW);                                                      
  digitalWrite(DRIVE_IN2,LOW);                                                      
} 

void direct_Motor(uint8_t p)                                                    
{
  if(p==D_ROTACAO_0_DESCIDA)                                                
  {
    digitalWrite(DRIVE_IN1,HIGH);                                                 
    digitalWrite(DRIVE_IN2,LOW);                                                 
  }
  else if(p==D_ROTACAO_1_SUBIDA)
  {                                                                    
    digitalWrite(DRIVE_IN1,LOW);                                             
    digitalWrite(DRIVE_IN2,HIGH);                                          
  }
} 

void set_Duty(uint8_t duty)                                                  
{
  OCR1A = duty;                                                              
}                                                                            

void motor_Init()
{
  TCCR1A = 0b10000001; 
  TCCR1B = 0b00001010; 

  pinMode(DRIVE_PWM, OUTPUT);
  pinMode(DRIVE_IN1, OUTPUT);
  pinMode(DRIVE_IN2, OUTPUT);
}                                                                            
