#ifndef BIBLIOTECAS_H
#define BIBLIOTECAS_H

#include <stdio.h>
#include <stdint.h>
#include <Arduino.h>
#include <math.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <AS5045.h>

#include "status.h"
#include "PINOUT.h"
#include "botao.h"
#include "tela.h"
#include "timers.h"
#include "motor.h"
#include "controle.h"
//----------------------------------------------------------------------------------------------------------------
//definições
#define   ALARM_DESLIGADO   0//set sistema desligado
#define   ALARM_LIGADO   1//set sistema ligado
#define   ALARM_PRESSAO_ALTA   2//inspiração 
#define   ALARM_PRESSAO_BAIXA   3//inspiração
#define   ALARM_ALTA_PEEP   4//expiração
#define   ALARM_VAZAMENTO   5//inspiração
#define   ALARM_VOLUME_MAX   6//inspiração_pressão

#define   MODO_OPERACAO_VOLUME   0     
#define   MODO_OPERACAO_PRESSAO   7

#define	  D_ROTACAO_0_SUBIDA   0
#define	  D_ROTACAO_1_DESCIDA   1

#define   POSICAO_SUP_LIMITE 1750
#define   POSICAO_INF_LIMITE 800

#define	  BTN_VERDE   'g'
#define	  BTN_DIREITA   'd'
#define	  BTN_BAIXO   'b'
#define	  BTN_CIMA   'c'
#define	  BTN_VERMELHO   'r'
#define	  BTN_ESQUERDA   'e'
//          telas
#define   D_TELA_CONFIG_0  '0'
#define   D_TELA_CONFIG_1  '1'
#define   D_MENU_PRESSAO   '2'
#define   D_MENU_VOLUME   '3'
#define   D_MENU_PEEP   '4'
#define   D_MENU_CALIBRA   '5'
#define   D_TELA_INICIAL  '6'
#define   D_TELA_COLLAB   '9'

//            SET
#define   D_INCREMENTO       1 
#define   D_DECREMENTO       2


//    LIMITES das variáveis da IHM INF e SUP 
#define   L_VOLUME_SUP   300
#define   L_VOLUME_INF   150

#define   L_PEEP_SUP  25
#define   L_PEEP_INF   0

#define   L_PRESSAO_SUP   50
#define   L_PRESSAO_INF    6

#define   L_PROP_RESP_SUP 30
#define   L_PROP_RESP_INF 10

#define   L_TEMP_INSP_SUP   1800
#define   L_TEMP_INSP_INF   1000

#define   L_PAUSE_EXP_SUP  500
#define   L_PAUSE_EXP_INF  350
//----------------------------------------------------------------------------------------------------------------	
#endif		
