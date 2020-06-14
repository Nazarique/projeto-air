#include "bibliotecas.h"


LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB7, LCD_DB6, LCD_DB5, LCD_DB4);

char estado = '0';

void machine_state()
{
  char botao = 0;
  static uint8_t cursor = 1;

  system_status_t *p_sys_status;
  config_t config_IHM_aux;

  p_sys_status = get_sys_status();

  switch(estado)
  {
    case D_TELA_CONFIG_0: // Essa é a tela principal
      botao = read_Button();

      if(!botao)
      {
        break;
      } 
      else if(botao == BTN_CIMA)
      {
        estado = D_TELA_CONFIG_0;
        if(cursor > 1)
        {
          cursor--; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO)
      {
        estado = D_TELA_CONFIG_0;
        if(cursor < 3)
        {
          cursor++; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para descida
      else if(botao == BTN_DIREITA)
      { 
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_1;
        screen_static(estado);
        screen_dynamic(estado);
      }//inicia
      else if(botao == BTN_VERDE)
      {
        switch(cursor)
        {
          case 1:
            screen_static(D_TELA_INICIAL);
            screen_dynamic(D_TELA_INICIAL);          
            break;
          case 2:
            screen_static(D_MENU_PRESSAO);
            screen_dynamic(D_MENU_PRESSAO);          
            break; 
          case 3:
            screen_static(D_MENU_VOLUME);
            screen_dynamic(D_MENU_VOLUME);          
            break;   
          //colocar um default
        }
        cursor = 1;
      }//botão verde pressionado 
      break;
      
    case D_TELA_CONFIG_1://config 2
      botao = read_Button();

      if(!botao)
      {
        break;
      } 
      else if(botao == BTN_CIMA)
      {
        estado = D_TELA_CONFIG_1;
        if(cursor > 1)
        {
          cursor--; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO)
      {
        estado = D_TELA_CONFIG_1;
        if(cursor < 2)
        {
          cursor++; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA)
      { 
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        screen_dynamic(estado);
      }//inicia
      else if(botao == BTN_VERDE)
      {
        switch(cursor)
        {
          case 1:
            screen_static(D_MENU_PEEP);
            screen_dynamic(D_MENU_PEEP);          
            break;
          case 2:
            screen_static(D_MENU_CALIBRA);
            screen_dynamic(D_MENU_CALIBRA);          
            break;   
          //colocar um default
        }
        cursor = 1;
      }//botão verde pressionado 
      break;

    case D_MENU_PRESSAO://pressão
      botao = read_Button();

      if(!botao)
      {
        break;
      } 
      else if(botao == BTN_CIMA)
      {
        estado = D_MENU_PRESSAO;
        if(cursor > 1)
        {
          cursor--; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO)
      {
        estado = D_MENU_PRESSAO;
        if(cursor < 2)
        {
          cursor++; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_TEMP_INSPI); 
            //SET DECREMENTO         
            break;
          case 2:
            screen_dynamic(D_SET_FREQ_RESPI); 
            //SET DECREMENTO
            break;   
          //colocar um default
        }
      }//Decremento
      else if(botao == BTN_DIREITA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_TEMP_INSPI); 
            //SET INCREMENTO         
            break;
          case 2:
            screen_dynamic(D_SET_FREQ_RESPI); 
            //SET INCREMENTO
            break;   
          //colocar um default
        }
      }//Incremento
      else if(botao == BTN_VERDE)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //Salva os valores 
      }//botão verde pressionado 
      else if(botao == BTN_VERMELHO)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //DESCATA OS VALORES
      }//botão verde pressionado 
      break;

    case D_MENU_VOLUME://volume
      botao = read_Button();

      if(!botao)
      {
        break;
      } 
      else if(botao == BTN_CIMA)
      {
        estado = D_MENU_VOLUME;
        if(cursor > 1)
        {
          cursor--; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO)
      {
        estado = D_MENU_VOLUME;
        if(cursor < 3)
        {
          cursor++; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_VOLUME); 
            //SET DECREMENTO         
            break;
          case 2:
            screen_dynamic(D_SET_TEMP_INSPI); 
            //SET DECREMENTO
            break;
          case 3:
            screen_dynamic(D_SET_FREQ_RESPI); 
            //SET DECREMENTO
            break;   
          //colocar um default
        }
      }//Decremento
      else if(botao == BTN_DIREITA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_VOLUME); 
            //SET INCREMENTO         
            break;
          case 2:
            screen_dynamic(D_SET_TEMP_INSPI); 
            //SET INCREMENTO
            break;   
          case 3:
            screen_dynamic(D_SET_FREQ_RESPI); 
            //SET INCREMENTO
            break;
          //colocar um default
        }
      }//Incremento
      else if(botao == BTN_VERDE)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //Salva os valores 
      }//botão verde pressionado 
      else if(botao == BTN_VERMELHO)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //DESCATA OS VALORES
      }//botão verde pressionado 
      break;

    case D_MENU_PEEP://peep
      botao = read_Button();

      if(!botao)
      {
        break;
      } 
      else if(botao == BTN_CIMA)
      {
        estado = D_MENU_VOLUME;
        if(cursor > 1)
        {
          cursor--; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO)
      {
        estado = D_MENU_VOLUME;
        if(cursor < 2)
        {
          cursor++; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_PEEP); 
            //SET DECREMENTO         
            break;
          case 2:
            screen_dynamic(D_SET_PAUSE_EXP); 
            //SET DECREMENTO         
            break;
          //colocar um default
        }
      }//Decremento
      else if(botao == BTN_DIREITA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_PEEP); 
            //SET INCREMENTO         
            break;
          case 2:
            screen_dynamic(D_SET_PAUSE_EXP); 
            //SET DECREMENTO         
            break;
          //colocar um default
        }
      }//Incremento
      else if(botao == BTN_VERDE)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //Salva os valores 
      }//botão verde pressionado 
      else if(botao == BTN_VERMELHO)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //DESCATA OS VALORES
      }//botão verde pressionado 
      break;

    case D_MENU_CALIBRA://calibra
      botao = read_Button();

      if(!botao)
      {
        break;
      } 
      else if(botao == BTN_CIMA)
      {
        estado = D_MENU_VOLUME;
        if(cursor > 1)
        {
          cursor--; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO)
      {
        estado = D_MENU_VOLUME;
        if(cursor < 1)
        {
          cursor++; 
        }
        screen_dynamic(estado);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_CALIBRA); 
            //SET DECREMENTO         
            break;
          //colocar um default
        }
      }//Decremento
      else if(botao == BTN_DIREITA)
      { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(D_SET_CALIBRA); 
            //SET INCREMENTO         
            break;
          //colocar um default
        }
      }//Incremento
      else if(botao == BTN_VERDE)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //Salva os valores 
      }//botão verde pressionado 
      else if(botao == BTN_VERMELHO)
      {
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        //DESCATA OS VALORES
      }//botão verde pressionado 
      break;

    case D_TELA_INICIAL://operando - inicio
      botao = read_Button();

      if(!botao)
      {
        break;
      } 
      else if(botao == BTN_ESQUERDA)
      {
        estado = D_TELA_CONFIG_0;  
        screen_static(estado);
      }//config
      else if(botao == BTN_VERMELHO)
      {
        estado = D_TELA_INICIAL;  
        screen_static(estado);
        set_sys_status(0);
      }//desliga
      else if (botao == BTN_VERDE)
      {
        estado = D_TELA_INICIAL;
        screen_static(estado);
        set_sys_status(1);
      }//liga
      break;  
  }
}

void screen_static(char p)
{
  switch(p)
  {
    case D_TELA_CONFIG_0: //Menu controles pagina 1
      lcd.clear();                                       
      lcd.setCursor(0, 0);                               
      lcd.print(" AIR --- Controles  ");
      lcd.setCursor(0, 1);                               
      lcd.print("   Início           ");
      lcd.setCursor(0, 2);                               
      lcd.print("   Pressão          ");
      lcd.setCursor(0, 3);                               
      lcd.print("   Volume      (1/2)");
      break;

    case D_TELA_CONFIG_1: //Menu controles pagina 2
      lcd.clear();                                       
      lcd.setCursor(0,0);
      lcd.print(" AIR --- Controles  ");
      lcd.setCursor(0,1);
      lcd.print("   PEEP             "); 
      lcd.setCursor(0,2);
      lcd.print("   Calibra          "); 
      lcd.setCursor(0,3);
      lcd.print("   Desliga     (2/2)"); 
      break;    

    case D_MENU_PRESSAO:  //tela pressão
      lcd.clear();                                       

      lcd.setCursor(0,0);
      lcd.print("  Insp-   XXX s     ");
      lcd.setCursor(0,1);
      lcd.print("  Freq-    XX R/min ");
      lcd.setCursor(0,2);
      lcd.print("    Pressao:  XX cm ");
      lcd.setCursor(0,3);
      lcd.print(" Retorna      Grava ");
      break;

    case D_MENU_VOLUME: //tela volume
      lcd.clear();                                       

      lcd.setCursor(0,0);
      lcd.print("  Volume-  XXXmL    ");
      lcd.setCursor(0,1);
      lcd.print("  Insp  -  XXXs     ");
      lcd.setCursor(0,2);
      lcd.print("  Freq  -   XXr/min ");
      lcd.setCursor(0,3);
      lcd.print(" Retorna      Grava ");
      break;        

    case D_MENU_PEEP:
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("  PEEP       :  XX  ");
      lcd.setCursor(0,2);
      lcd.print("  Pause Exp -  XXXs ");
      lcd.setCursor(0,3);
      lcd.print(" Retorna      Grava ");
      break;

    case D_MENU_CALIBRA:
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("  TESTE      :  XX  ");
      lcd.setCursor(0,3);
      lcd.print(" Retorna      Grava ");
      break;

    case D_TELA_INICIAL: // tela iniciar 
      lcd.clear();                                       
      lcd.setCursor(0, 0);                               
      lcd.print(" P/V Corrente: XXX  ");
      lcd.setCursor(0, 1);                               
      lcd.print(" T. Inspira  : XXX  ");
      lcd.setCursor(0, 2);                               
      lcd.print(" Frequencia  : XXX  ");
      lcd.setCursor(0, 3);                               
      lcd.print(" Retorna            ");
      break;  

    case D_TELA_COLLAB:  // Mantida pelo meme 
      lcd.clear();                                        
      lcd.setCursor(0, 0);                                
      lcd.print("  COLLAB - AIR_ONE  "); 
      lcd.setCursor(0, 2);                                
      lcd.print(" RESETING.");

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

void screen_dynamic(control_t *controle, config_t *IHM_aux, char p)						//tela dynamic
{
	char col = 16;
	switch(p)
	{
		case D_MENU_PRESSAO:	//tela print pressão                                       
			lcd.setCursor(col, 0);                               
			lcd.print(controle->c_pressao_PEEP);//var atual

			lcd.setCursor(col, 1);                               
			lcd.print(IHM_aux->PEEP);//var de ajuste
			break;

		case D_MENU_VOLUME:	//tela volume  

			lcd.setCursor(col, 0);                               
			lcd.print(controle->c_angulo_final);//var atual

			lcd.setCursor(col, 1);                               
			lcd.print(IHM_aux->angulo);//var de ajuste
			break;				

		case D_MENU_FREQ_RES:	//tela freq                                       
			lcd.setCursor(col, 0);                               
			lcd.print(controle->c_pwm_insp);//var atual

			lcd.setCursor(col, 1);                               
			lcd.print(IHM_aux->pwm);//var de ajuste
			break;

		case D_MENU_TEMP_INS: //tela tempo insp                        
			lcd.setCursor(col, 0);                               
			lcd.print(controle->c_pwm_insp);//var atual

			lcd.setCursor(col, 1);                               
			lcd.print(IHM_aux->pwm);//var de ajuste
			break;

		case D_TELA_INICIAL: // tela iniciar // pressão                                    
			lcd.setCursor(12, 0);                               
			lcd.print("Pressao");

			lcd.setCursor(1, 3);                               
			lcd.print("Pressao def:");

			lcd.setCursor(13, 3);
			lcd.print(controle->c_pwm_insp);
			break;		

		case D_TELA_INICIAL_V: // tela iniciar // volume                                    
			lcd.setCursor(12, 0);                               
			lcd.print("Volume");

			lcd.setCursor(1, 3);                               
			lcd.print("Volume def:");

			lcd.setCursor(13, 3);
			lcd.print(controle->c_angulo_final);
			break;			
	}
}

void set_IHM_volume(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_volume<=L_VOLUME_SUP)
        {
          IHM_aux->h_volume+=10;
        }
        break;
    case D_DECREMENTO:
        if(IHM_aux->h_volume>=L_VOLUME_INF)
        {
          IHM_aux->h_volume-=10;
        }
        break;
  }
}

void set_IHM_peep(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_peep<=L_PEEP_SUP)
        {
          IHM_aux->h_peep+=5;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_peep>=L_PEEP_INF)
        {
          IHM_aux->h_peep-=5;
        }
        break;
  }
}

void set_IHM_pressao(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_pressao<=L_PRESSAO_SUP)
        {
          IHM_aux->h_pressao+=5;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_pressao>=L_PRESSAO_INF)
        {
          IHM_aux->h_pressao-=5;
        }
        break;
  }
}

void set_IHM_freqResp(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_freq<=L_FREQ_RESP_SUP)
        {
          IHM_aux->h_freq+=5;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_freq>=L_FREQ_RESP_INF)
        {
          IHM_aux->h_freq-=5;
        }
        break;
  }
}

void set_IHM_tempInsp(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_temp_insp<=L_TEMP_INSP_SUP)
        {
          IHM_aux->h_temp_insp+=5;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_temp_insp>=L_TEMP_INSP_INF)
        {
          IHM_aux->h_temp_insp-=5;
        }
        break;
  }
}

void set_IHM_pauseExp(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_pause_exp<=L_PAUSE_EXP_SUP)
        {
          IHM_aux->h_pause_exp+=5;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_pause_exp>=L_PAUSE_EXP_INF)
        {
          IHM_aux->h_pause_exp-=5;
        }
        break;
  }
}

void screen_Init()
{
	lcd.begin(20, 4);
	screen_static(D_TELA_COLLAB);
  screen_static(estado);

  pinMode(LCD_PWM, OUTPUT);
  OCR1C = 120; // AJUSTE DA TELA 
}