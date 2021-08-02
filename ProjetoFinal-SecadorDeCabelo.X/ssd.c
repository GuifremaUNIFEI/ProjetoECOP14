// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: ssd.c
//            Biblioteca de controle dos displays de 7 segmentos
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------


#include "ssd.h"
#include "io.h"
#include <pic18f4520.h>

#define DATA  PORTD
#define DISP0 PIN_A2
#define DISP1 PIN_A3
#define DISP2 PIN_A4
#define DISP3 PIN_A5

//vetor para armazenar a conversão do display
static const char valor[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
//armazena qual é o display disponivel
static char display;
//armazena o valor a ser enviado ao display
static char v0, v1, v2, v3;

void ssdDigit(char val, char pos) {
    if (pos == 0) {
        v0 = val;
    }
    if (pos == 1) {
        v1 = val;
    }
    if (pos == 2) {
        v2 = val;
    }
    if (pos == 3) {
        v3 = val;
    }

}

void ssdUpdate(void) {
    
    //portd é compartilhado
    //então tem q garantir que é saida
    TRISD= 0x00;
    //desliga todos os displays
    digitalWrite(DISP0,LOW);
    digitalWrite(DISP1,LOW);
    digitalWrite(DISP2,LOW);
    digitalWrite(DISP3,LOW);
    
    //desliga todos os leds
    DATA = 0x00;

    
    switch (display) //liga apenas o display da vez
    {
        case 0:
            DATA = valor[v0];
            digitalWrite(DISP0,HIGH);
            display = 1;
            break;

        case 1:
            DATA = valor[v1];
            digitalWrite(DISP1,HIGH);
            display = 2;
            break;

        case 2:
            DATA = valor[v2];
            digitalWrite(DISP2,HIGH);
            display = 3;
            break;

        case 3:
            DATA = valor[v3];
            digitalWrite(DISP3,HIGH);
            display = 0;
            break;

        default:
            display = 0;
            break;
    }
}

void ssdInit(void) {
    //configuração dos pinos de controle
    pinMode(DISP0, OUTPUT);
    pinMode(DISP1, OUTPUT);
    pinMode(DISP2, OUTPUT);
    pinMode(DISP3, OUTPUT);
    
    //Porta de dados como saida
    TRISD = 0x00; 

}