// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de operação de um teclado matricial
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

#include "keypad.h"
#include <pic18f4520.h>
#include "io.h"
#include "bits.h"

static unsigned int valor = 0x0000;

#define LIN0 PIN_D0
#define LIN1 PIN_D1
#define LIN2 PIN_D2
#define LIN3 PIN_D3
#define COL0 PIN_B0 
#define COL1 PIN_B1
#define COL2 PIN_B2

unsigned int kpRead(void) {
    return valor;
}

void kpDebounce(void) {
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned int valorNovo = 0x0000;
    static unsigned int valorAntigo = 0x0000;

    //store D to avoid mess with other periphels
    unsigned char old_D;
    old_D = PORTD;
    
    //PORTD é compartilhado, então tem
    //que garantir que é entrada
    TRISD |= 0x0f;
    
    for (i = 0; i < 3; i++) {
        //desabilita todas as colunas
        TRISB &= 0xF8;
        //Habilita apenas a coluna desejada
        bitSet(TRISB,i);
        //coloca nivel alto só na coluna desejada
        PORTB |= 0x07;
        bitClr(PORTB, i);
        
        //delay pra estabilizar os sinais
        for (int k = 0; k < 10; k++);

        //realiza o teste para cada bit e atualiza a variável
        for (j = 0; j < 4; j++) {
            if (!bitTst(PORTD, j)) {
                bitSet(valorNovo, (i * 4) + j);
            } else {
                bitClr(valorNovo, (i * 4) + j);
            }
        }
    }
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }
    PORTD = old_D;
    TRISD = 0x00;
}

void kpInit(void) {
    //coloca 0-2 como saída
    TRISB &= 0x07;
    //coloca 0-3 como entrada
    TRISD |= 0x0f;  
}