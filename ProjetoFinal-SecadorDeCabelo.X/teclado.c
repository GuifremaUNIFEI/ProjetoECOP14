#include "pic18f4520.h"
#include "teclado.h"
#include "delay.h"

// TC0 PORTDbits.RD3 BitTst(PORTD,3)
// TC1 PORTDbits.RD2 BitTst(PORTD,2)
// TC2 PORTDbits.RD1 BitTst(PORTD,1)
// TC3 PORTDbits.RD0 BitTst(PORTD,0)

const unsigned char linha[4] = {TL1, TL2, TL3};
unsigned int atraso_min = 5;
unsigned int atraso = 15;

unsigned char tc_tecla(unsigned int timeout) {
    unsigned int to = 0;
    unsigned char i;
    unsigned char ret = 0;
    unsigned char tmp = PORTB;


    while (((to < timeout) || (!timeout))&&(!ret)) {
        for (i = 0; i < 3; i++) {
            PORTB |= ~linha[i];
            if (!BitTst(PORTD,3)) { //TC1
                atraso_ms(atraso);
                if (!BitTst(PORTD,3)) {
                    while (!BitTst(PORTD,3));
                    ret = 1 + i;
                    break;
                }
            };
            if (!BitTst(PORTD,2)) {
                atraso_ms(atraso);
                if (!BitTst(PORTD,2)) {
                    while (!BitTst(PORTD,2));
                    ret = 4 + i;
                    break;
                }
            };
            if (!BitTst(PORTD,1)) {
                atraso_ms(atraso);
                if (!BitTst(PORTD,1)) {
                    while (!BitTst(PORTD,1));
                    ret = 7 + i;
                    break;
                }
            };
            if (!BitTst(PORTD,0)) {
                atraso_ms(atraso);
                if (!BitTst(PORTD,0)) {
                    while (!BitTst(PORTD,0));
                    ret = 10 + i;
                    break;
                }
            };
            PORTB &= linha[i];
        };
        atraso_ms(atraso_min);
        to += 5;
    }

    if (!ret)ret = 255;
    if (ret == 11)ret = 0;
    PORTB = tmp;
    return ret;
}


