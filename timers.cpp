#include "bibliotecas.h"

uint8_t flag_control_stat_machine = 0;
uint32_t global_counter = 0; 

system_timer watch_insp;
system_timer watch_exp;
//relógios de precisão para contagem dos ciclos de respiração

//----------------------------------------------------------------------------------------------------------------       
void timer_set(system_timer *timer, uint32_t interval)
{
  timer->timer_start = global_counter;
  timer->timer_interval = interval;
  return;
}
//----------------------------------------------------------------------------------------------------------------       
void timer_reset(system_timer *timer)
{
  timer->timer_start = global_counter;
  return;
}
//----------------------------------------------------------------------------------------------------------------       
uint8_t timer_expired(system_timer *timer)
{
  uint8_t expired = 0;

  if (global_counter - timer->timer_start > timer->timer_interval)
  {
    expired = 1;
  }
  return expired;
}
//----------------------------------------------------------------------------------------------------------------       
void watch_set(system_timer *timer)
{
  timer->timer_start = global_counter;
  return;
}
//----------------------------------------------------------------------------------------------------------------       
uint32_t watch_get(system_timer *timer)
{
  return global_counter - timer->timer_start;
}
//----------------------------------------------------------------------------------------------------------------       
uint32_t get_global_counter()
{
  return global_counter;
}
//----------------------------------------------------------------------------------------------------------------       
ISR(TIMER4_OVF_vect)                                                           
{ 
  TCNT4 = 49536;

  global_counter++;

  deadTimeButton_Isr();

  if(!flag_control_stat_machine)
  {
    flag_control_stat_machine = 1;
  }

}
//----------------------------------------------------------------------------------------------------------------       
void interrupt4_OVF_Init()
{  
  TCCR4A = 0x00;                                                               
  TCCR4B = 0x01;                                                               
  TCNT4 = 49536;                                                               
  TIMSK4 = 0x01;          

  // --- Time counter =  ( ( 2^16 - 49536)   x   (Prescaler=1)  /  16E+6 = 1ms ---                                                     
}//  end init interrupt



