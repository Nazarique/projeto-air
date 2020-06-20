#include "bibliotecas.h"

void serial()
{
  if(Serial.read() == '1'){
  digitalWrite(27,!digitalRead(27));
  control_t * control;
  control = get_control();
  
  data dado = {0};
  dado.angulo = control->c_angulo_encoder;
  dado.pressao = (analogRead(P_SENSOR_PRESSAO)-48)*0.1105;
  
  const int capacity = JSON_OBJECT_SIZE(2);//nosso documento Json possui no 2 valores;  
  StaticJsonDocument<capacity> doc;
  
  doc["pressao"] = dado.pressao;
  doc["angulo"] = dado.angulo;
 
  
  serializeJson(doc, Serial);
  Serial.println(); 
  
  }
}

ISR(TIMER4_OVF_vect)                                                           
{ 
  static uint16_t cont = 100;
  TCNT4 = 49536;
  deadTimeButton_Isr();
  maqEstados_Control();
  

  if(--cont==0){
    serial();
    cont = 100;
  }
  
}

void interrupt4_OVF_Init()
{  
  TCCR4A = 0x00;                                                               
  TCCR4B = 0x01;                                                               
  TCNT4 = 49536;                                                               
  TIMSK4 = 0x01;          
  // --- Time counter =  ( ( 2^16 - 49536)   x   (Prescaler=1)  /  16E+6 = 1ms ---                                                     
}                                                                            //  end ini interrupt
