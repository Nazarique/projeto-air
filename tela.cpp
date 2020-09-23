#include "bibliotecas.h"


LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB7, LCD_DB6, LCD_DB5, LCD_DB4);

static char estado = '0';

config_t get_IHM_default()
{
  config_t IHM;
  memset(&IHM, 0, sizeof(config_t));

  control_t *s_control;
  s_control = get_control();

  IHM.h_peep = s_control->c_pressao_PEEP;
  IHM.h_pressao = s_control->c_pressao_cont;
  IHM.h_prop = L_PROP_RESP_INF;
  IHM.h_volume = L_VOLUME_SUP;
  IHM.h_freq = 20;
  IHM.h_temp_insp = s_control->c_tempo_insp_IHM + s_control->c_tempo_exp_pause;
  IHM.h_pause_exp = s_control->c_tempo_exp_pause;

  return IHM;
}

void machine_state()
{
  char botao = 0;
  float freq_auxiliar = 0;
  static uint8_t cursor = 1;

  system_status_t *p_sys_status;
  p_sys_status = get_sys_status();
  
  static config_t config_IHM_aux = get_IHM_default();
  // inicia uma variavel do tipo IHM_config zerando a struct e forncendo valores iniciais
  switch(estado)
  {
    case D_TELA_CONFIG_0:                   // Menu principal parte 1, configura volume pressao e inicia
      botao = read_Button();     
      if(!botao) {
       
        break;
      } 
      else if(botao == BTN_CIMA){
        estado = D_TELA_CONFIG_0;
        if(cursor > 1)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor--; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO){
        estado = D_TELA_CONFIG_0;
        if(cursor < 3)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor++; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para descida
      else if(botao == BTN_DIREITA){ 
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_1;
        screen_static(estado);
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//inicia
      else if(botao == BTN_VERDE){
          config_IHM_aux.h_volume = 3451.0 / 1.85 - (float) p_sys_status->s_control.c_angulo_final / 1.85;        // Quando o botao verde eh apertado
                                                                                      // as variaveis sao salvas 
          config_IHM_aux.h_temp_insp = p_sys_status->s_control.c_tempo_insp_IHM;     // na estrutura auxiliar
                                                                                      // 
          freq_auxiliar =  60000.0/(float)(p_sys_status->s_control.c_tempo_exp_cont +          // 
                                           p_sys_status->s_control.c_tempo_insp_cont +        // A estrutura auxiliar eh o que 
                                           p_sys_status->s_control.c_tempo_exp_pause);        // possibilita a alteracao de 
                                                                                      // dados na interface
          config_IHM_aux.h_freq = freq_auxiliar;        //                            //
          config_IHM_aux.h_prop = (p_sys_status->s_control.c_tempo_exp_ocioso + 550) * 10 / p_sys_status->s_control.c_tempo_insp_IHM;
          config_IHM_aux.h_pressao = p_sys_status->s_control.c_pressao_cont;          // 

        switch(cursor)
        {
          case 1:                           //
            config_IHM_aux.h_temp_insp = p_sys_status->s_control.c_tempo_insp_cont;     // na estrutura auxiliar
            estado = D_TELA_INICIAL;        //
            break;                          // a tela destino eh baseada na opcao 
          case 2:                           // em que o cursor eh setado
            cursor = 0;                     //
            estado = D_MENU_PRESSAO;        //
            break;                          //
          case 3:                           //
            cursor = 0;                     //
            estado = D_MENU_VOLUME;         //
            break;                          //
        }
          screen_static(estado);
          screen_dynamic(&config_IHM_aux, estado, cursor);
      }
      break;
      
    case D_TELA_CONFIG_1:                   // Menu principal parte 2, com configuracao de PEEP calibracao e desligar motor
      botao = read_Button();

      if(!botao) {
        //screen_dynamic(&config_IHM_aux, estado, cursor);
        break;
      } 
      else if(botao == BTN_CIMA) {
        estado = D_TELA_CONFIG_1;
        if(cursor > 1)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor--; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO) {
        estado = D_TELA_CONFIG_1;
        if(cursor < 3)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor++; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA) { 
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;
        screen_static(estado);
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//inicia
      else if(botao == BTN_VERDE){
        config_IHM_aux.h_peep = p_sys_status->s_control.c_pressao_PEEP;
        config_IHM_aux.h_pause_exp = p_sys_status->s_control.c_tempo_exp_pause;
        switch(cursor){
          case 1:
            estado = D_MENU_PEEP;
            break;
          case 2:
            estado = D_MENU_CALIBRA;
            break;   
          case 3:
            cursor = 1;
            estado = D_TELA_CONFIG_0;
            set_sys_status(0);
            break;
        }
        screen_static(estado);
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//botão verde pressionado 
      break;

    case D_MENU_PRESSAO:            //Config de pressão
      botao = read_Button();        // com ajustes de tempo insp 
                                    // e prop respiratoria
      if(!botao){                             
        break;
      } 
      else if(botao == BTN_CIMA){
        if(cursor > 0)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor--; 
        }
        estado = D_MENU_PRESSAO;
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO){
        if(cursor < 2)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor++; 
        }
        estado = D_MENU_PRESSAO;
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA){ 
        switch(cursor) {
          case 0: //tempo inspiratorio
            set_IHM_tempInsp(&config_IHM_aux, D_DECREMENTO);
            break;
          case 1: //frequencia
            set_IHM_proporcao(&config_IHM_aux, D_DECREMENTO);
            break;   
          case 2: //pressao   
            set_IHM_pressao(&config_IHM_aux, D_DECREMENTO);
            break;   
        }
        estado = D_MENU_PRESSAO;
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//Decremento
      else if(botao == BTN_DIREITA){ 
        switch(cursor){
          case 0://tempo inspiratorio
            set_IHM_tempInsp(&config_IHM_aux, D_INCREMENTO);
            break;
          case 1: //frequencia
            set_IHM_proporcao(&config_IHM_aux, D_INCREMENTO);
            break;   
          case 2: //pressao
            set_IHM_pressao(&config_IHM_aux, D_INCREMENTO);
            break;   
        }
        estado = D_MENU_PRESSAO;
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//Incremento
      else if(botao == BTN_VERDE) {
        cursor = 2;//RESET CURSOR
        estado = D_TELA_INICIAL;            // Salvando valores
        screen_static(estado);              // 

        set_sys_modOperacao(MODO_OPERACAO_PRESSAO);
        set_control_tempoInspiratorioIHM(config_IHM_aux.h_temp_insp);
        set_control_tempoExpiratorioIHM(config_IHM_aux.h_prop);
        set_control_pressao(config_IHM_aux.h_pressao);
      }
      else if(botao == BTN_VERMELHO){
        cursor = 1;                   //
        estado = D_TELA_CONFIG_0;     // volta a tela inicial
        screen_static(estado);        //
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//botão verde pressionado 
      break;

    case D_MENU_VOLUME://volume
      botao = read_Button();

      if(!botao){
        break;
      } 
      else if(botao == BTN_CIMA){
        estado = D_MENU_VOLUME;
        if(cursor > 0)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor--; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO){
        estado = D_MENU_VOLUME;
        if(cursor < 2)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor++; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA) { 
        switch(cursor)
        {
          case 0: // volume 
            set_IHM_volume(&config_IHM_aux, D_DECREMENTO);
            break;
          case 1: // Tempo inspi 
            set_IHM_tempInsp(&config_IHM_aux, D_DECREMENTO);
            break;
          case 2: // freq respiratoria 
            set_IHM_proporcao(&config_IHM_aux, D_DECREMENTO);
            break;   
          //colocar um default
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//Decremento
      else if(botao == BTN_DIREITA){ 
        switch(cursor){
          case 0: // volume 
            set_IHM_volume(&config_IHM_aux, D_INCREMENTO);
            break;
          case 1: // Tempo inspi 
            set_IHM_tempInsp(&config_IHM_aux, D_INCREMENTO);
            break;
          case 2: // prop respiratoria 
            set_IHM_proporcao(&config_IHM_aux, D_INCREMENTO);
            break;   
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//Incremento
      else if(botao == BTN_VERDE){
        cursor = 1;//RESET CURSOR       //
        estado = D_TELA_INICIAL;       // Salva valores
        screen_static(estado);          //
        screen_dynamic(&config_IHM_aux, estado, cursor);

        set_sys_modOperacao(MODO_OPERACAO_VOLUME);
        set_control_tempoInspiratorioIHM(config_IHM_aux.h_temp_insp);
        set_control_tempoExpiratorioIHM(config_IHM_aux.h_prop);
        set_control_angulo(config_IHM_aux.h_volume);
      }
      else if(botao == BTN_VERMELHO){
        cursor = 1;//RESET CURSOR      //                      
        estado = D_TELA_CONFIG_0;      // volta a tela inicial 
        screen_static(estado);         //                      
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//botão verde pressionado 
      break;

    case D_MENU_PEEP://peep
      botao = read_Button();

      if(!botao) {
        break;
      } 
      else if(botao == BTN_CIMA) {
        estado = D_MENU_PEEP;
        if(cursor > 1)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor--; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO) {
        estado = D_MENU_PEEP;
        if(cursor < 2)
        {
          lcd.setCursor(1,cursor);
          lcd.print(" ");
          cursor++; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA){ 
        switch(cursor){
          case 1: // peep
            set_IHM_peep(&config_IHM_aux, D_DECREMENTO);
            break;
          case 2: //pausa expiratoria
            set_IHM_pauseExp(&config_IHM_aux, D_DECREMENTO);
            break;
        }
        estado = D_MENU_PEEP;
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//Decremento
      else if(botao == BTN_DIREITA){ 
        switch(cursor){
          case 1: // peep
            set_IHM_peep(&config_IHM_aux, D_INCREMENTO);
            break;
          case 2: //pausa expiratoria
            set_IHM_pauseExp(&config_IHM_aux, D_INCREMENTO);
            break;
        }
        estado = D_MENU_PEEP;
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//Incremento
      else if(botao == BTN_VERDE){
        cursor = 1;//RESET CURSOR
        estado = D_TELA_CONFIG_0;                       //
        screen_static(estado);                          // Salva valores
        screen_dynamic(&config_IHM_aux, estado, cursor);

        set_control_PEEP(config_IHM_aux.h_peep);        //
        set_control_pause(config_IHM_aux.h_pause_exp);  //
      }//botão verde pressionado 
      else if(botao == BTN_VERMELHO){
        cursor = 1;//RESET CURSOR           //                      
        estado = D_TELA_CONFIG_0;           // volta a tela inicial 
        screen_static(estado);              //                      
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//botão verde pressionado 
      break;

    case D_MENU_CALIBRA://calibra
      botao = read_Button();

      if(!botao) {
        break;
      } 
      else if(botao == BTN_CIMA) {
        estado = D_MENU_VOLUME;
        if(cursor > 1)
        {
          cursor--; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para subida
      else if(botao == BTN_BAIXO) {
        estado = D_MENU_VOLUME;
        if(cursor < 1)
        {
          cursor++; 
        }
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//seleção do cursor para descida
      else if(botao == BTN_ESQUERDA) { 
        switch(cursor)
        {
          case 1:
            estado = D_MENU_CALIBRA; 
            screen_dynamic(&config_IHM_aux, estado, cursor);
            //SET DECREMENTO         
            break;
          //colocar um default
        }
      }//Decremento
      else if(botao == BTN_DIREITA) { 
        switch(cursor)
        {
          case 1:
            screen_dynamic(&config_IHM_aux, estado, cursor); 
            //SET INCREMENTO         
            break;
          //colocar um default
        }
      }//Incremento
      else if(botao == BTN_VERDE) {
        cursor = 1;//RESET CURSOR   // A opcao de calibragem
        estado = D_TELA_CONFIG_0;   // ainda nao esta disponivel
        screen_static(estado);      // mas tem seu espaco aqui
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//botão verde pressionado 
      else if(botao == BTN_VERMELHO) {
        cursor = 1;//RESET CURSOR  //                      
        estado = D_TELA_CONFIG_0;  // volta a tela inicial 
        screen_static(estado);     //                   
        screen_dynamic(&config_IHM_aux, estado, cursor);   
      }//botão verde pressionado 
      break;

    case D_TELA_INICIAL://operando - inicio
      botao = read_Button();
      config_IHM_aux.h_temp_insp = p_sys_status->s_control.c_tempo_insp_cont;

      freq_auxiliar =  60000.0/(float)(p_sys_status->s_control.c_tempo_exp_cont +          // 
                         p_sys_status->s_control.c_tempo_insp_cont +        // A estrutura auxiliar eh o que 
                         p_sys_status->s_control.c_tempo_exp_pause);        // possibilita a alteracao de 
                                                                            // dados na interface
      config_IHM_aux.h_freq = freq_auxiliar;       
      screen_dynamic(&config_IHM_aux, estado, cursor);
      if(!botao) {                        // 
        break;                            // TODO
      }                                   // 
      else if(botao == BTN_VERMELHO) {    // [ ] interface bonita para 
        estado = D_TELA_CONFIG_0;         //        volume e pressao
        screen_static(estado);            // [ ] saber o volume com 
        screen_dynamic(&config_IHM_aux, estado, cursor);
      }//config                           //        base no encoder
      else if (botao == BTN_VERDE) {      // 
        estado = D_TELA_INICIAL;          // 
        screen_static(estado);            // 
        screen_dynamic(&config_IHM_aux, estado, cursor);
        set_sys_status(1);                // 
      }//liga
      break;  
  }
}

//        
//        
//        Tela Estatica
//        
//
//----------------------------------------------------------------------------------------------------------------
void screen_static(char p)
{
  switch(p)
  {
    case D_TELA_CONFIG_0: //Menu controles pagina 1
      lcd.clear();                                    
      lcd.setCursor(0, 0);                               
      lcd.print(" AIR --- Controles  ");       // nao tem muito o que comentar
      lcd.setCursor(0, 1);                     // acho que eh mais facil olhar          
      lcd.print("   Iniciar          ");       // a imagem no google drive pra 
      lcd.setCursor(0, 2);                     // entender o sistema de telas
      lcd.print("   Pressao          ");       //
      lcd.setCursor(0, 3);                     // mas as telas estaticas sao basicamente
      lcd.print("   Volume      (1/2)");       // o que nao vai se mexer (ava) nos menus
      break;

    case D_TELA_CONFIG_1: //Menu controles pagina 2
      lcd.clear();                                     
      lcd.setCursor(0,0);
      lcd.print(" AIR --- Controles  ");
      lcd.setCursor(0,1);
      lcd.print("   PEEP / Pausa Exp "); 
      lcd.setCursor(0,2);
      lcd.print("   Calibra          "); 
      lcd.setCursor(0,3);
      lcd.print("   Desliga     (2/2)"); 
      break;    

    case D_MENU_PRESSAO:  //tela pressão
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("  Insp :  XXX s     ");
      lcd.setCursor(0,1);
      lcd.print("  Prop : 1:XXXs     ");
      lcd.setCursor(0,2);
      lcd.print("  Pressao:    XX cm ");
      lcd.setCursor(0,3);
      lcd.print(" Retorna      Grava ");
      break;

    case D_MENU_VOLUME: //tela volume
      lcd.clear();  
      lcd.setCursor(0,0);
      lcd.print("  Volume : XXXXmL   ");
      lcd.setCursor(0,1);
      lcd.print("  Insp   : XXXX s   ");
      lcd.setCursor(0,2);
      lcd.print("  Prop   : 1:XXX s  ");
      lcd.setCursor(0,3);
      lcd.print(" Retorna      Grava ");
      break;        

    case D_MENU_PEEP:
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("  PEEP      :  Xcm  ");
      lcd.setCursor(0,2);
      lcd.print("  Pausa Exp : XXXXs ");
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
      lcd.print("     Corrente:      ");
      lcd.setCursor(0, 1);                               
      lcd.print(" T. Inspira  :      ");
      lcd.setCursor(0, 2);                               
      lcd.print(" Frequencia  :      ");
      lcd.setCursor(0, 3);                               
      lcd.print(" Retorna            ");
      break;  

    case D_TELA_COLLAB:  // Mantida pelo meme 
      lcd.clear();                                        
      lcd.setCursor(0, 0);                                
      lcd.print("  COLLAB - AIR_ONE  "); 
      lcd.setCursor(0, 2);                                
      lcd.print(" RESETING.");

      delay(100);                                         
      lcd.print(".");

      delay(100);
      lcd.print(".");

      delay(100);
      lcd.print(".");

      delay(100);
      lcd.print(".");
      break;
  }
}

//////////////////////////////////////////////////////////////        
//        Tela Dinamica                                     //
//////////////////////////////////////////////////////////////        
//----------------------------------------------------------------------------------------------------------------
void screen_dynamic(config_t *IHM_aux, char p, uint8_t cursor)
{
  char col = 16;
  switch(p)
  {
    case D_TELA_CONFIG_0:
      lcd.setCursor(1,cursor);    // aqui a gente 
      lcd.print("~");             // coloca o cursor
      break;

    case D_TELA_CONFIG_1:
      lcd.setCursor(1,cursor);    // aqui a gente 
      lcd.print("~");             // coloca o cursor
      break;

    case D_MENU_PRESSAO:  //tela print pressão                                       
      lcd.setCursor(1,cursor);    // aqui a gente 
      lcd.print("~");             // coloca o cursor

      lcd.setCursor(10, 0);                         //      
      lcd.print("    ");//                          // Limpamos os valores "anteriores"
      lcd.setCursor(10, 0);                         //            e
      lcd.print((uint8_t)(IHM_aux->h_temp_insp/1000));         //
      lcd.print(",");                               // colocamos os valores de 
      lcd.print((uint8_t)((IHM_aux->h_temp_insp%1000)/100));   // tempo insp, frequencia 
                                                    //
      lcd.setCursor(11, 1);                         // e -futuramente- pressao
      lcd.print("   ");//                           //
      lcd.setCursor(11, 1);                         //       
      lcd.print((uint8_t)(IHM_aux->h_prop/10));                //
      lcd.print(",");                               // 
      lcd.print((uint8_t)(IHM_aux->h_prop%10));                //
                                                    //
      lcd.setCursor(14, 2);                         //       
      lcd.print("   ");//                           //
      lcd.setCursor(14, 2);                         //       
      lcd.print((uint8_t)(IHM_aux->h_pressao));                //
      break;

    case D_MENU_VOLUME: //tela volume  

      lcd.setCursor(1,cursor);    // aqui a gente 
      lcd.print("~");             // coloca o cursor

      lcd.setCursor(11, 0);                          //
      lcd.print("    ");//                           //
      lcd.setCursor(11, 0);                          //
      lcd.print((uint8_t)(IHM_aux->h_volume));                  // Limpam-se os valores setados
                                                     // anteriormente e apos isso
      lcd.setCursor(11, 1);                          // printar os valores de 
      lcd.print("    ");//                           // calibracao
      lcd.setCursor(11, 1);                          //
      lcd.print((uint8_t)(IHM_aux->h_temp_insp/1000));          //
      lcd.print(",");                                //
      lcd.print((uint8_t)((IHM_aux->h_temp_insp%1000)/100));    //
                                                     //
      lcd.setCursor(13, 2);                          //
      lcd.print("   ");//                            //
      lcd.setCursor(13, 2);                          //
      lcd.print((uint8_t)(IHM_aux->h_prop/10));                 //
      lcd.print(",");                                // 
      lcd.print((uint8_t)(IHM_aux->h_prop%10));                 //
      break;        

    case D_MENU_PEEP:
      lcd.setCursor(1,cursor);    // aqui a gente 
      lcd.print("~");             // coloca o cursor
                                                      // Limpam-se os valores setados 
      lcd.setCursor(14, 1);                           // anteriormente e apos isso    
      lcd.print("  ");//                              // printar os valores de        
      lcd.setCursor(14, 1);                           // calibracao                   
      lcd.print((uint8_t)(IHM_aux->h_peep));                     //                              
                                                      //                              
      lcd.setCursor(14, 2);                           //                              
      lcd.print("  ");//                              //                              
      lcd.setCursor(14, 2);                           //                              
      lcd.print(IHM_aux->h_pause_exp/1000);           //                              
      lcd.print(",");                                 //
      lcd.print((uint8_t)((IHM_aux->h_pause_exp%1000)/10));      //                              
                                                                                    
      break;                                                                        
                                                                                    
    case D_MENU_CALIBRA:                              // não fiz nada aqui
      lcd.setCursor(2, 0);                            // não fiz nada aqui
      lcd.print("  ");

      lcd.setCursor(15, 0);                           // não fiz nada aqui   
      lcd.print((uint8_t)(IHM_aux->h_pressao));

      lcd.setCursor(15, 1);                           // não fiz nada aqui   
      lcd.print((uint8_t)(IHM_aux->h_temp_insp));

      lcd.setCursor(15, 2);                           // não fiz nada aqui   
      lcd.print((uint8_t)(IHM_aux->h_prop));
      break;

    case D_TELA_INICIAL: // tela inicial                                    
      lcd.setCursor(cursor, 0);                       // 
      lcd.print(get_sys_modOperacaoIHM());                 // TODO
                                                      //  [ ] uma tela inicial decente
      lcd.setCursor(15, 0);                           //  que entenda quando eh volume e  
      if(get_sys_modOperacaoIHM() == 'P'){lcd.print(IHM_aux->h_pressao);} //   pressao
      if(get_sys_modOperacaoIHM() == 'V'){lcd.print(IHM_aux->h_volume);}  //
                                                      //
      lcd.setCursor(15, 1);                           //
      lcd.print((uint8_t)(IHM_aux->h_temp_insp/1000));//         //
      lcd.print(",");                                 //
      lcd.print((uint8_t)((IHM_aux->h_temp_insp%1000)/100));     //
                                                      //
      lcd.setCursor(15, 2);                           //    
      lcd.print("   ");
      lcd.setCursor(15, 2);      //    
      lcd.print((uint8_t)(IHM_aux->h_freq));
      break;      
  }
}

//////////////////////////////////////////////////////////////////////////////////        
//        Sets de variaveis, incremento e decremento                            //
////////////////////////////////////////////////////////////////////////////////// 
//----------------------------------------------------------------------------------------------------------------       
void set_IHM_volume(config_t *IHM_aux, uint8_t p)     //seta volume
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_volume<L_VOLUME_SUP)
        {
          IHM_aux->h_volume+=10;
        }
        break;
    case D_DECREMENTO:
        if(IHM_aux->h_volume>L_VOLUME_INF)
        {
          IHM_aux->h_volume-=10;
        }
        break;
  }
}
//----------------------------------------------------------------------------------------------------------------
void set_IHM_peep(config_t *IHM_aux, uint8_t p)     // seta Peep
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_peep<L_PEEP_SUP)
        {
          IHM_aux->h_peep+=1;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_peep>L_PEEP_INF)
        {
          IHM_aux->h_peep-=1;
        }
        break;
  }
}
//----------------------------------------------------------------------------------------------------------------
void set_IHM_pressao(config_t *IHM_aux, uint8_t p) {
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_pressao<L_PRESSAO_SUP)
        {
          IHM_aux->h_pressao+=1;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_pressao>L_PRESSAO_INF)
        {
          IHM_aux->h_pressao-=1;
        }
        break;
  }
}
//----------------------------------------------------------------------------------------------------------------
void set_IHM_proporcao(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_prop<L_PROP_RESP_SUP)
        {
          IHM_aux->h_prop+=2;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_prop>L_PROP_RESP_INF)
        {
          IHM_aux->h_prop-=2;
        }
        break;
  }
}
//----------------------------------------------------------------------------------------------------------------
void set_IHM_tempInsp(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_temp_insp<L_TEMP_INSP_SUP)
        {
          IHM_aux->h_temp_insp+=100;
        }
        break;
        
    case D_DECREMENTO:
        if(IHM_aux->h_temp_insp>L_TEMP_INSP_INF)
        {
          IHM_aux->h_temp_insp-=100;
        }
        break;
  }
}
//----------------------------------------------------------------------------------------------------------------
void set_IHM_pauseExp(config_t *IHM_aux, uint8_t p)
{
  switch(p)
  {
    case D_INCREMENTO:  
        if(IHM_aux->h_pause_exp<L_PAUSE_EXP_SUP)
        {
          IHM_aux->h_pause_exp+=50;                  
        }                                             
        break;                                        
                                                     
    case D_DECREMENTO:                               
        if(IHM_aux->h_pause_exp>L_PAUSE_EXP_INF)     
        {                                            
          IHM_aux->h_pause_exp-=50;                  
        }
        break;
  }
}
///////////////////////////////////////////////////////////////        
//        Inicializacao                                      //
/////////////////////////////////////////////////////////////// 
//----------------------------------------------------------------------------------------------------------------       
void screen_Init()
{
  pinMode(LCD_PWM, INPUT);
  //OCR1C = 120; // AJUSTE DA TELA 
  
  lcd.begin(20, 4);
  screen_static(D_TELA_COLLAB);

  { //configurações para tela inicial
    screen_static(estado);
    lcd.setCursor(1,1);    // aqui a gente 
    lcd.print("~");             // coloca o cursor
  }
}
