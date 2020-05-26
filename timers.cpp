#include "bibliotecas.h"

ISR(TIMER4_OVF_vect)                                                           
{ 
  TCNT4 = 49536;
  //encoder();
  //inverte_Rotacao();  
  deadTimeButton_Isr();
  deadTimeMotor_Isr();
  degrauTime_Isr();
}

void interrupt4_OVF_Init()
{  
  TCCR4A = 0x00;                                                               
  TCCR4B = 0x02;                                                               
  TCNT4 = 49536;                                                               
  TIMSK4 = 0x01;          
  // --- Time counter =  ( ( 2^16 - 49536)   x   (Prescaler=1)  /  16E+6 = 1ms ---                                                     
}                                                                            //  end ini interrupt
