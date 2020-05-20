#include "bibliotecas.h"


LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB7, LCD_DB6, LCD_DB5, LCD_DB4);

char estado = '0';

void machine_state()
{
  char botao = 0;
  switch(estado)
  {
    case D_TELA_CONFIG_0://config 1     
      botao = read_Button();

      if(!botao)
      {
		break;
      } 
      else if(botao == D_CARACTER_BOTAO_1)
      {
        estado = D_MENU_PRESSAO;
        screen_static(estado);
      }//pressao
      else if(botao == D_CARACTER_BOTAO_2)
      { 
        estado = D_MENU_VOLUME;
        screen_static(estado);
      }//volume
      else if(botao == D_CARACTER_BOTAO_5)
      { 
        estado = D_TELA_INICIAL;
        screen_static(estado);
      }//inicia
      else if(botao == D_CARACTER_BOTAO_3)
      {
        estado = D_TELA_CONFIG_1;
        screen_static(estado);
      }//prox 
      break;

    case D_TELA_CONFIG_1://config 2
      botao = read_Button();

	  if(!botao)
	  {
	  	break;
	  } 
      else if(botao == D_CARACTER_BOTAO_1)
      { 
        estado = D_MENU_FREQ_RES; 
        screen_static(estado);
      }//frequencia 
      else if(botao == D_CARACTER_BOTAO_2)
      {
        estado = D_MENU_TEMP_INS; 
        screen_static(estado); 
      }//tempo
      else if(botao == D_CARACTER_BOTAO_5)
      { 
        estado = D_TELA_INICIAL;  
        screen_static(estado); 
      }//inicia
      else if(botao == D_CARACTER_BOTAO_3)
      { 
        estado = D_TELA_CONFIG_0; 
        screen_static(estado); 
      }//volta  
      break;

    case D_MENU_PRESSAO://pressão
      botao = read_Button();
      
      if(!botao)
	  {
	  	break;
	  } 
      else if(botao == D_CARACTER_BOTAO_1)
      { 
        estado = D_MENU_PRESSAO;  
        screen_dynamic(estado);
      } //inc
      else if(botao == D_CARACTER_BOTAO_2)
      { 
        estado = D_MENU_PRESSAO;  
        screen_dynamic(estado);
      } //dec

      else if(botao == D_CARACTER_BOTAO_3)
      { 
        estado = D_TELA_INICIAL;  
        screen_static(estado);
      }//salva
      else if(botao == D_CARACTER_BOTAO_4)
      { 
        estado = D_TELA_INICIAL;  
        screen_static(estado);
      }//esc  
      break;

    case D_MENU_VOLUME://volume
      botao = read_Button();
	  if(!botao)
	  {
	  	break;
	  } 
      else if(botao == D_CARACTER_BOTAO_1)
      { 
        estado = D_MENU_VOLUME; 
        screen_dynamic(estado);
      } //inc
      else if(botao == D_CARACTER_BOTAO_2)
      { 
        estado = D_MENU_VOLUME; 
        screen_dynamic(estado); 
      } //dec

      else if(botao == D_CARACTER_BOTAO_3)
      { 
        estado = D_TELA_INICIAL;  
        screen_static(estado); 
      }//salva
      else if(botao == D_CARACTER_BOTAO_4)
      {
        estado = D_TELA_INICIAL;
        screen_static(estado);
      }//esc  
      break;

    case D_MENU_FREQ_RES://frequencia
      botao = read_Button();
	  if(!botao)
	  {
	  	break;
	  } 
      else if(botao == D_CARACTER_BOTAO_1)
      { 
        estado = D_MENU_FREQ_RES;
        screen_dynamic(estado);
      } //inc
      else if(botao == D_CARACTER_BOTAO_2)
      { 
        estado = D_MENU_FREQ_RES; 
        screen_dynamic(estado); 
      } //dec

      else if(botao == D_CARACTER_BOTAO_3)
      { 
        estado = D_TELA_INICIAL;  
        screen_static(estado); 
      }//salva
      else if(botao == D_CARACTER_BOTAO_4)
      { 
        estado = D_TELA_INICIAL;  
        screen_static(estado); 
      }//esc  
      break;

    case D_MENU_TEMP_INS://tempo
      botao = read_Button();
      
      if(!botao)
	  {
	  	break;
	  } 
      else if(botao == D_CARACTER_BOTAO_1)
      { 
        estado = D_MENU_TEMP_INS;
        screen_dynamic(estado); 
      } //inc
      else if(botao == D_CARACTER_BOTAO_2){
        estado = D_MENU_TEMP_INS;
        screen_dynamic(estado);
      } //dec

      else if(botao == D_CARACTER_BOTAO_3)
      {
        estado = D_TELA_INICIAL;
        screen_static(estado);
      }//salva
      else if(botao == D_CARACTER_BOTAO_4)
      {
        estado = D_TELA_INICIAL;  
        screen_static(estado); 
      }//esc  
      break;  

    case D_TELA_INICIAL://operando - inicio
      botao = read_Button();
      
      if(!botao)
	  {
	  	break;
	  } 
      else if(botao == D_CARACTER_BOTAO_5)
      {//config
      }
      else if(botao == D_CARACTER_BOTAO_6)
      {

      }//desliga
      break;  
  }
}
void screen_static(char p)						//tela Static
{
	char col = 1;
	switch(p)
	{
		case D_TELA_CONFIG_0:	//tela modo de operação
			lcd.clear();                                       
			lcd.setCursor(col, 0);                               
			lcd.print("1 - Pressao");

			lcd.setCursor(col, 1);                               
			lcd.print("2 - Volume");

			lcd.setCursor(col, 2);                               
			lcd.print("Verde - Inicia");

			lcd.setCursor(col, 3);                               
			lcd.print("Enter - Prox. Pag.");
			break;

		case D_TELA_CONFIG_1://tela de operação tela prox. pag.
			lcd.clear();                                       
			lcd.setCursor(col, 0);                               
			lcd.print("1 - Freq. Resp.");

			lcd.setCursor(col, 1);                               
			lcd.print("2 - Tempo Insp.");

			lcd.setCursor(col, 2);                               
			lcd.print("Verde - Inicia");

			lcd.setCursor(col, 3);                               
			lcd.print("Enter - Prox. Pag.");
			break;		

		case D_MENU_PRESSAO:	//tela pressão
			lcd.clear();                                       
			lcd.setCursor(col, 0);                               
			lcd.print("Pressao: Atual - ");

			lcd.setCursor(col+10, 1);                               
			lcd.print("Ajuste - ");

			lcd.setCursor(col, 2);                               
			lcd.print("1 - Inc");

			lcd.setCursor(col+10, 2);                               
			lcd.print("2 - Dec");

			lcd.setCursor(col, 3);                               
			lcd.print("<- Salva");

			lcd.setCursor(col+10, 3);                               
			lcd.print("x - Esc");
			break;

		case D_MENU_VOLUME:	//tela volume
			lcd.clear();                                       
			lcd.setCursor(col, 0);                               
			lcd.print("Volume: Atual - ");

			lcd.setCursor(col+10, 1);                               
			lcd.print("Ajuste - ");

			lcd.setCursor(col, 2);                               
			lcd.print("1 - Inc");

			lcd.setCursor(col+10, 2);                               
			lcd.print("2 - Dec");

			lcd.setCursor(col, 3);                               
			lcd.print("<- Salva");

			lcd.setCursor(col+10, 3);                               
			lcd.print("x - Esc");
			break;				

		case D_MENU_FREQ_RES:	//tela freq
			lcd.clear();                                       
			lcd.setCursor(col, 0);                               
			lcd.print("Freq/min: Atual:");

			lcd.setCursor(col+10, 1);                               
			lcd.print("Ajuste:");

			lcd.setCursor(col, 2);                               
			lcd.print("1 - Inc");

			lcd.setCursor(col+10, 2);                               
			lcd.print("2 - Dec");

			lcd.setCursor(col, 3);                               
			lcd.print("<- Salva");

			lcd.setCursor(col+10, 3);                               
			lcd.print("x - Esc");
			break;

		case D_MENU_TEMP_INS: //tela tempo insp
			lcd.clear();                                       
			lcd.setCursor(1, 0);                               
			lcd.print("T. Insp.: Atual-");

			lcd.setCursor(col+10, 1);                               
			lcd.print("Ajuste:");

			lcd.setCursor(col, 2);                               
			lcd.print("1 - Inc");

			lcd.setCursor(col+10, 2);                               
			lcd.print("2 - Dec");

			lcd.setCursor(col, 3);                               
			lcd.print("<- Salva");

			lcd.setCursor(col+10, 3);                               
			lcd.print("x - Esc");
			break;

		case D_TELA_INICIAL: // tela iniciar 
			lcd.clear();                                       
			lcd.setCursor(col, 0);                               
			lcd.print("Modo Oper: ");

			lcd.setCursor(col, 1);                               
			lcd.print("Freq.  Resp: ");

			lcd.setCursor(col, 2);                               
			lcd.print("Temp. Insp: ");
			break;	

		case D_TELA_COLLAB:
			lcd.clear();                                        
			lcd.setCursor(col, 0);                                
			lcd.print("COLLAB - AIR_ONE"); 
			lcd.setCursor(col, 2);                                
			lcd.print("RESETING.");

			delay(500);                                         
			lcd.print(".");

			delay(500);
			lcd.print(".");

			delay(500);
			lcd.print(".");

			delay(500);
			lcd.print(".");

			delay(500);
			break;

	}
}

void screen_dynamic(char p)						//tela dynamic
{
	char col = 17;
	switch(p)
	{
		case D_MENU_PRESSAO:	//tela print pressão                                       
			lcd.setCursor(col, 0);                               
			lcd.print("60");//var atual

			lcd.setCursor(col, 1);                               
			lcd.print("50");//var de ajuste
			break;

		case D_MENU_VOLUME:	//tela volume                    
			lcd.setCursor(col, 0);                               
			lcd.print("600");//var atual

			lcd.setCursor(col, 1);                               
			lcd.print("700");//var de ajuste
			break;				

		case D_MENU_FREQ_RES:	//tela freq                                       
			lcd.setCursor(col, 0);                               
			lcd.print("23");//var atual

			lcd.setCursor(col, 1);                               
			lcd.print("7");//var de ajuste
			break;

		case D_MENU_TEMP_INS: //tela tempo insp                        
			lcd.setCursor(col, 0);                               
			lcd.print("3");//var atual

			lcd.setCursor(col, 1);                               
			lcd.print("2");//var de ajuste
			break;

		case D_TELA_INICIAL: // tela iniciar // pressão                                    
			lcd.setCursor(12, 0);                               
			lcd.print("Pressao");

			lcd.setCursor(1, 3);                               
			lcd.print("Pressao def:");

			lcd.setCursor(13, 3);
			lcd.print("90");
			break;		

		case D_TELA_INICIAL_V: // tela iniciar // volume                                    
			lcd.setCursor(12, 0);                               
			lcd.print("Volume");

			lcd.setCursor(1, 3);                               
			lcd.print("Volume def:");

			lcd.setCursor(13, 3);
			lcd.print("40");
			break;			
	}
}

void screen_Init()
{
	lcd.begin(20, 4);
  screen_static(estado);
}
