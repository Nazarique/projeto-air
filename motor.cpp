#include "bibliotecas.h"

volatile motorAux_t flag_Motor = {0};

void deadTimeMotor_Isr()                                                      
{
  static unsigned char cont20 = 20;

  if(flag_Motor.deadTime)                                                        
  {
    if(--cont20==0)                                                           
    { 
      cont20 = 20;                                                            
      flag_Motor.deadTime = 0; 
      direct_Motor(flag_Motor.direcao);  //duvida                                                                                                           
    }
  }
}

void change_Motor(uint8_t p)   
{
  flag_Motor.direcao = p;

  if(flag_Motor.Adirecao!=flag_Motor.direcao)       
  {
    stop_Motor();               
    flag_Motor.deadTime = 1;
  }
  else
  {
    direct_Motor(flag_Motor.direcao);  
  }
}

void stop_Motor()
{                                  
  digitalWrite(DRIVE_IN1,LOW);                                                      
  digitalWrite(DRIVE_IN2,LOW);  
  flag_Motor.stop = 1;                                                    
} 

void direct_Motor(uint8_t p)                                                    
{
  flag_Motor.stop = 0;

  if(p==D_ROTACAO_0_DESCIDA)                                                
  {
    digitalWrite(DRIVE_IN1,HIGH);                                                 
    digitalWrite(DRIVE_IN2,LOW);
    flag_Motor.Adirecao = 0;                                                  
  }
  else if(p==D_ROTACAO_1_SUBIDA)
  {                                                                    
    digitalWrite(DRIVE_IN1,LOW);                                             
    digitalWrite(DRIVE_IN2,HIGH);  
    flag_Motor.Adirecao = 1;                                          
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
