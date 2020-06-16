#include "bibliotecas.h"

void serial()
{
  data dado;
  dado.pressao = (analogRead(P_SENSOR_PRESSAO)-48)*0.1105;  
  dado.fluxo = dado.pressao/2;
  dado.volume = dado.pressao*2;
  
  const int capacity = JSON_OBJECT_SIZE(3);//nosso documento Json possui no 3 valores;  
  StaticJsonDocument<capacity> doc;

  doc["pressao"] = dado.pressao;
  doc["fluxo"] = dado.fluxo;
  doc["volume"] = dado.volume;
  
  
  serializeJson(doc, Serial);
  Serial.println(); 
  
}

ISR(TIMER4_OVF_vect)                                                           
{ 
  TCNT4 = 49536;
  deadTimeButton_Isr();
  maqEstados_Control();
}

void interrupt4_OVF_Init()
{  
  TCCR4A = 0x00;                                                               
  TCCR4B = 0x01;                                                               
  TCNT4 = 49536;                                                               
  TIMSK4 = 0x01;          
  // --- Time counter =  ( ( 2^16 - 49536)   x   (Prescaler=1)  /  16E+6 = 1ms ---                                                     
}                                                                            //  end ini interrupt
