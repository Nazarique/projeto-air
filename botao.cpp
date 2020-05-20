#include "bibliotecas.h"

button_t flag_button = {0};

void deadTimeButton_Isr()                                                      
{
  static unsigned char cont5 = 5;                                                      

  if(flag_button.deadTime)                                                        
  {
    if(--cont5==0)                                                           
    { 
    	cont5 = 5;                                                            
    	flag_button.deadTime = 0;                                                                                                              
    }
  }
}

char detect_Button()
{
	char button = 0;

	if(digitalRead(B_bt1)!=flag_button.b1)
	{
		if(flag_button.b1)
		{ 
			flag_button.b1=0;
			button = D_CARACTER_BOTAO_1; 
			flag_button.deadTime=1;
		}	
		else
		{
			flag_button.b1=1;
			flag_button.deadTime=1; 
		} 
	} 
	else if(digitalRead(B_bt2)!=flag_button.b2)
	{
		if(flag_button.b2)
		{ 
			flag_button.b2=0;	
			button = D_CARACTER_BOTAO_2; 
			flag_button.deadTime=1; 
		}	
		else
		{		 		
			flag_button.b2=1;	
			flag_button.deadTime=1; 
		} 
	} 
  else if(digitalRead(B_bt3)!=flag_button.b3)
	{
		if(flag_button.b3)
		{ 
			flag_button.b3=0;	
			button = D_CARACTER_BOTAO_3; 
			flag_button.deadTime=1; 
		}	
		else
		{		 		
			flag_button.b3=1;	
			flag_button.deadTime=1; 
		} 
	} 

	else if(digitalRead(B_bt4)!=flag_button.b4)
	{
		if(flag_button.b4)
		{ 
			flag_button.b4=0;	
			button = D_CARACTER_BOTAO_4; 
			flag_button.deadTime=1; 
		}	
		else
		{		 		
			flag_button.b4=1;	
			flag_button.deadTime=1; 
		} 
	} 

	else if(digitalRead(B_bt5)!=flag_button.b5)
	{
		if(flag_button.b5)
		{ 
			flag_button.b5=0;	
			button = D_CARACTER_BOTAO_5; 
			flag_button.deadTime=1; 
		}	
		else
		{		 		
			flag_button.b5=1;	
			flag_button.deadTime=1; 
		} 
	} 

	else if(digitalRead(B_bt6)!=flag_button.b6)
	{
		if(flag_button.b6)
		{ 
			flag_button.b6=0;	
			button = D_CARACTER_BOTAO_6; 
			flag_button.deadTime=1; 
		}	
		else
		{		 		
			flag_button.b6=1;	
			flag_button.deadTime=1; 
		} 
	} 
	return button;
}

char read_Button()
{
	char button = 0;
	if(!flag_button.deadTime)
	{
	  button = detect_Button();
	}
 
	return button;
}

void button_Init()
{
	pinMode(B_bt1, INPUT);
	pinMode(B_bt2, INPUT);
	pinMode(B_bt3, INPUT);
	pinMode(B_bt4, INPUT);
	pinMode(B_bt5, INPUT);
	pinMode(B_bt6, INPUT);
}
