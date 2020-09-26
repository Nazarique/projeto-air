#ifndef BIBLIOTECAS_H
#define BIBLIOTECAS_H

#include <stdio.h>
#include <stdint.h>
#include <Arduino.h>
#include <math.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include "status.h"
#include "PINOUT.h"
#include "botao.h"
#include "tela.h"
#include "timers.h"
#include "motor.h"
#include "controle.h"
//--------------------------------------------------------------------------------------------------------
//definições
#define   S_ENCODER_AS5045  
//idef usados para a escolha do encoder

#define   ALARM_DESLIGADO   0//set sistema desligado
#define   ALARM_LIGADO   1//set sistema ligado
#define   ALARM_PRESSAO_ALTA   2//inspiração 
#define   ALARM_PRESSAO_BAIXA   3//inspiração
#define   ALARM_ALTA_PEEP   4//expiração
#define   ALARM_VAZAMENTO   5//inspiração
#define   ALARM_VOLUME_MAX   6//inspiração_pressão
//alarmes podem ser encontrados no timer.cpp

#define   T_DEAD_TIME_MOTOR   350     
#define   T_PERIODO_DA_RAMPA 	5
#define   T_DEBOUNCE_BOTOES 	5
//tempo de contadores auxiliares, como no caso debounce para botões e 
//dead time para motor

#define   T_PERIODO_IHM 		50
#define   T_PERIODO_SERIAL_ALARM 300
//periodo de repetição para as funções serial e ihm

#define   MODO_OPERACAO_VOLUME   0     
#define   MODO_OPERACAO_PRESSAO   7
//modos de operação de nosso respirador
//os mesmo são usados no controle (controle.cpp)
//tem um if de comparação na função de expiração 

#define	  D_ROTACAO_0_SUBIDA   0
#define	  D_ROTACAO_1_DESCIDA   1
//sentidos de rotação

#define   POSICAO_SUP_LIMITE 1750
#define   POSICAO_INF_LIMITE 800
//limites para angulos do encoder

#define	  BTN_VERDE   'g'
#define	  BTN_DIREITA   'd'
#define	  BTN_BAIXO   'b'
#define	  BTN_CIMA   'c'
#define	  BTN_VERMELHO   'r'
#define	  BTN_ESQUERDA   'e'
//definições dos botões para tela.cpp

//          telas
#define   D_TELA_CONFIG_0  '0'
#define   D_TELA_CONFIG_1  '1'
#define   D_MENU_PRESSAO   '2'
#define   D_MENU_VOLUME   '3'
#define   D_MENU_PEEP   '4'
#define   D_MENU_CALIBRA   '5'
#define   D_TELA_INICIAL  '6'
#define   D_TELA_COLLAB   '9'
//definições das telas

//            SET
#define   D_INCREMENTO       1 
#define   D_DECREMENTO       2
//usados para a seleção de botões, onde o botrão de cima
//simboliza incremento
//e o botão de baixo
//simboliza decremento

//    LIMITES das variáveis da IHM INF e SUP 
#define   L_VOLUME_SUP   300
#define   L_VOLUME_INF   150
//limites para ovolume que se encontra na inspiração

#define   L_PEEP_SUP  25
#define   L_PEEP_INF   0
//limites para a pressão peep (pressão minima)

#define   L_PRESSAO_SUP   50
#define   L_PRESSAO_INF    6
//limites para a pressão que se encontra na inspiração

#define   L_PROP_RESP_SUP 30
#define   L_PROP_RESP_INF 10
//proproção de ciclo respiratório
// (INSPIRAÇÃO + PAUSA ) / EXPIRAÇÃO

#define   L_TEMP_INSP_SUP   1800
#define   L_TEMP_INSP_INF   900
//tempo limite para inspiração, chamado de temp_insp + temp_pause, 
//no controle a contagem é feita apenas do tempo onde o motor
//se encontra dewscendo com a válvula fechada, mas na IHM
//este valor incrementa a pausa expiratória
//(ocorre na função expiração, mas faz parte do ciclo de inspiração)

#define   L_TEMP_EXP_SUP   5000
#define   L_TEMP_EXP_INF   1000
//tempo limite para expiração, chamado de exp_ocioso, 
//onde o motor sobe com a válvula aberta

#define   L_PAUSE_EXP_SUP  500
#define   L_PAUSE_EXP_INF  350
//tempo onde o motor fica parado com a válvula fechada 
//(ocorre na função expiração, mas faz parte do ciclo de inspiração)
//----------------------------------------------------------------------------------------------------------------	
#endif		
