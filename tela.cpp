#include "bibliotecas.h"


LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB7, LCD_DB6, LCD_DB5, LCD_DB4);

char estado = '0';

void machine_state()
{
  char botao = 0;

  system_status *p_sys_status;
  config_t config_IHM_aux;
  
  p_sys_status = get_sys_status();
  
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
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
      }//pressao
      else if(botao == D_CARACTER_BOTAO_2)
      { 
        estado = D_MENU_VOLUME;
        screen_static(estado);
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
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
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
      }//frequencia 
      else if(botao == D_CARACTER_BOTAO_2)
      {
        estado = D_MENU_TEMP_INS; 
        screen_static(estado); 
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
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
		    set_IHM_PEEP(&config_IHM_aux, D_INCREMENTO);
        screen_static(estado);
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
      } //inc
      else if(botao == D_CARACTER_BOTAO_2)
      { 
        estado = D_MENU_PRESSAO;  
        set_IHM_PEEP(&config_IHM_aux, D_DECREMENTO);
        screen_static(estado);
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
      } //dec

      else if(botao == D_CARACTER_BOTAO_3)
      { 
        estado = D_TELA_CONFIG_0;
        set_control_PEEP(config_IHM_aux.PEEP);
        screen_static(estado);
      }//salva
      else if(botao == D_CARACTER_BOTAO_4)
      { 
        estado = D_TELA_CONFIG_0;  
        config_IHM_aux.PEEP = p_sys_status->s_control.c_pressao_PEEP;
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
        set_IHM_angulo(&config_IHM_aux, D_INCREMENTO);
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
      } //inc
      else if(botao == D_CARACTER_BOTAO_2)
      { 
        estado = D_MENU_VOLUME; 
        set_IHM_angulo(&config_IHM_aux, D_DECREMENTO);
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado); 
      } //dec

      else if(botao == D_CARACTER_BOTAO_3)
      { 
        estado = D_TELA_CONFIG_0;
        set_control_angulo(config_IHM_aux.angulo);
        
        screen_static(estado); 
      }//salva
      else if(botao == D_CARACTER_BOTAO_4)
      {
        estado = D_TELA_CONFIG_0;
        config_IHM_aux.angulo = p_sys_status->s_control.c_angulo_final;
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
          set_IHM_PWM(&config_IHM_aux, D_INCREMENTO);
          screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
        } //inc
        else if(botao == D_CARACTER_BOTAO_2)
        { 
          estado = D_MENU_FREQ_RES; 
          set_IHM_PWM(&config_IHM_aux, D_DECREMENTO);
          screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado); 
        } //dec
        else if(botao == D_CARACTER_BOTAO_3)
        { 
          estado = D_TELA_CONFIG_0;
          set_control_pwm(config_IHM_aux.pwm);
          screen_static(estado); 
        }//salva
        else if(botao == D_CARACTER_BOTAO_4)
        { 
          estado = D_TELA_CONFIG_0;  
          config_IHM_aux.pwm = p_sys_status->s_control.c_pwm_insp;
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
        set_IHM_PWM(&config_IHM_aux, D_INCREMENTO);
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado); 
      } //inc
      else if(botao == D_CARACTER_BOTAO_2){
        estado = D_MENU_TEMP_INS;
        set_IHM_PWM(&config_IHM_aux, D_DECREMENTO);
        screen_dynamic(&p_sys_status->s_control, &config_IHM_aux, estado);
      } //dec
      else if(botao == D_CARACTER_BOTAO_3)
      {
        estado = D_TELA_CONFIG_0;
        set_control_pwm(config_IHM_aux.pwm);
        screen_static(estado);
      }//salva
      else if(botao == D_CARACTER_BOTAO_4)
      {
        estado = D_TELA_CONFIG_0; 
        config_IHM_aux.pwm = p_sys_status->s_control.c_pwm_insp;
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
      {
      	estado = D_TELA_CONFIG_0;  
        screen_static(estado);
      }//config
      else if(botao == D_CARACTER_BOTAO_6)
      {
      	estado = D_TELA_INICIAL;  
        screen_static(estado);
        set_sys_status(0);
      }//desliga
      else if (botao == D_CARACTER_BOTAO_2)
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
  char col = 1;
  switch(p)
  {
    case D_TELA_CONFIG_0: //tela modo de operação
      lcd.clear();                                       
      lcd.setCursor(col, 0);                               
      lcd.print("M - Pressao");

      lcd.setCursor(col, 1);                               
      lcd.print("Vo - Volume");

      lcd.setCursor(col, 2);                               
      lcd.print("Ve - Inicia");

      lcd.setCursor(col, 3);                               
      lcd.print("L - Prox. Pag.");
      break;

    case D_TELA_CONFIG_1://tela de operação tela prox. pag.
      lcd.clear();                                       
      lcd.setCursor(col, 0);                               
      lcd.print("M - Freq. Resp.");

      lcd.setCursor(col, 1);                               
      lcd.print("Vo -Tempo Insp");

      lcd.setCursor(col, 2);                               
      lcd.print("Ve - Inicia");

      lcd.setCursor(col, 3);                               
      lcd.print("L - Prox. Pag.");
      break;    

    case D_MENU_PRESSAO:  //tela pressão
      lcd.clear();                                       
      lcd.setCursor(col, 0);                               
      lcd.print("Pressao: Atual:");

      lcd.setCursor(col+8, 1);                               
      lcd.print("Ajuste:");

      lcd.setCursor(col, 2);                               
      lcd.print("M - Inc");

      lcd.setCursor(col+10, 2);                               
      lcd.print("Vo - Dec");

      lcd.setCursor(col, 3);                               
      lcd.print("L- Salva");

      lcd.setCursor(col+10, 3);                               
      lcd.print("A - Esc");
      break;

    case D_MENU_VOLUME: //tela volume
      lcd.clear();                                       
      lcd.setCursor(col, 0);                               
      lcd.print("Volume: Atual:");

      lcd.setCursor(col+8, 1);                               
      lcd.print("Ajuste:");

      lcd.setCursor(col, 2);                               
      lcd.print("M - Inc");

      lcd.setCursor(col+10, 2);                               
      lcd.print("Vo - Dec");

      lcd.setCursor(col, 3);                               
      lcd.print("L- Salva");

      lcd.setCursor(col+10, 3);                               
      lcd.print("A - Esc");
      break;        

    case D_MENU_FREQ_RES: //tela freq
      lcd.clear();                                       
      lcd.setCursor(col, 0);                               
      lcd.print("Freq Atual:");

      lcd.setCursor(col+8, 1);                               
      lcd.print("Ajuste:");

      lcd.setCursor(col, 2);                               
      lcd.print("M - Inc");

      lcd.setCursor(col+10, 2);                               
      lcd.print("Vo - Dec");

      lcd.setCursor(col, 3);                               
      lcd.print("L- Salva");

      lcd.setCursor(col+10, 3);                               
      lcd.print("A - Esc");
      break;

    case D_MENU_TEMP_INS: //tela tempo insp
      lcd.clear();                                       
      lcd.setCursor(1, 0);                               
      lcd.print("T Insp: Atual:");

      lcd.setCursor(col+8, 1);                               
      lcd.print("Ajuste:");

      lcd.setCursor(col, 2);                               
      lcd.print("M - Inc");

      lcd.setCursor(col+10, 2);                               
      lcd.print("Vo - Dec");

      lcd.setCursor(col, 3);                               
      lcd.print("L- Salva");

      lcd.setCursor(col+10, 3);                               
      lcd.print("A - Esc");
      break;

    case D_TELA_INICIAL: // tela iniciar 
      lcd.clear();                                       
      lcd.setCursor(col, 0);                               
      lcd.print("Modo Oper: ");

      lcd.setCursor(col, 1);                               
      lcd.print("Freq.  Resp: ");

      lcd.setCursor(col, 2);                               
      lcd.print("Temp. Insp: ");

      lcd.setCursor(col, 3);                               
      lcd.print("6- Liga");

      lcd.setCursor(col+10, 3);                               
      lcd.print("2 - Des");
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

void set_IHM_PWM(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->pwm<=130)
        {
          IHM_aux->pwm+=10;
        }
        break;
    case D_DECREMENTO:
        if(IHM_aux->pwm>=20)
        {
          IHM_aux->pwm-=10;
        }
        break;
  }
}

void set_IHM_angulo(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->angulo<=240)
        {
          IHM_aux->angulo+=5;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->angulo>=120)
        {
          IHM_aux->angulo-=5;
        }
        break;
  }
}

void set_IHM_PEEP(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->PEEP<=20)
        {
          IHM_aux->PEEP+=5;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->PEEP>=4)
        {
          IHM_aux->PEEP-=5;
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
