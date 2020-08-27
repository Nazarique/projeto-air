#include "bibliotecas.h"

#define    ALARM_DESLIGADO      0//set sistema desligado
#define    ALARM_LIGADO         1//set sistema ligado
#define    ALARM_PRESSAO_ALTA   2//inspiração 
#define    ALARM_PRESSAO_BAIXA  3//inspiração
#define    ALARM_ALTA_PEEP      4//expiração
#define    ALARM_VAZAMENTO      5//inspiração
#define    ALARM_VOLUME_MAX     6//inspiração_pressão

#define    MODO_OPERACAO_VOLUME  0     
#define    MODO_OPERACAO_PRESSAO 7


uint8_t pwm_buzzer = 255;

void alarmes(){

 
  switch(get_sys_alarm()) {
  
  case 0:
      digitalWrite(L_LED_VERDE, LOW);
      
   break;
  
  case 1:
      digitalWrite(L_LED_VERDE, HIGH);
      digitalWrite(L_LED_VERMELHO, LOW);
      digitalWrite(B_ALARM_BUZZER, 0);
    break;
  case 2:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
    break;

  case 3:
   break;
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
  case 4:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
   break;

  case 5:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
   break;

  case 6:
      digitalWrite(L_LED_VERMELHO, HIGH);
      digitalWrite(B_ALARM_BUZZER, pwm_buzzer);
   break;

  default:
      digitalWrite(L_LED_VERDE, HIGH);
      digitalWrite(L_LED_VERMELHO, LOW);
      digitalWrite(B_ALARM_BUZZER, 0);
    break;
  }
  switch(get_sys_modOperacaoIHM()){
    case 'P':
      digitalWrite(L_LED_AZUL, HIGH);
      digitalWrite(L_LED_AMARELO, LOW);
      break;

   
   case 'V':
      digitalWrite(L_LED_AMARELO, HIGH);
      digitalWrite(L_LED_AZUL, LOW);
      break;
      
  }
}
void serial()
{  
  //digitalWrite(27,!digitalRead(27));
  
  data dado = {0};
  dado.alarm = get_sys_alarm();
  dado.angulo = get_control_anguloEncoder();
  dado.pressao = (analogRead(P_SENSOR_PRESSAO)-48)*0.1105;
  
  const int capacity = JSON_OBJECT_SIZE(3);//nosso documento Json possui no 3 valores;  
  StaticJsonDocument<capacity> doc;
  
  doc["alarm"] = dado.alarm;
  doc["pressao"] = dado.pressao;
  doc["angulo"] = dado.angulo;
 
  serializeJson(doc, Serial);
  Serial.println(); 
  
}

ISR(TIMER4_OVF_vect)                                                           
{ 
  TCNT4 = 49536;
  static uint16_t cont = 300;
  deadTimeButton_Isr();
  maqEstados_Control();
  
  if(--cont==0){
    serial();
    alarmes();
    cont = 300;
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
