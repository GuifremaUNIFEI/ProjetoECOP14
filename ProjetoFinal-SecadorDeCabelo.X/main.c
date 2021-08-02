#include "config.h"
#include "bits.h"
#include "lcd.h"
#include "keypad.h"
#include <pic18f4520.h>
#include "pwm.h"

void main(void) {
    TRISC = 0x00;
    TRISE = 0x00;
    unsigned int tecla = 16;
    lcdInit();
    kpInit();
    pwmInit();

    for (;;) {
        //Desliga o secador
        PORTCbits.RC5 = 0;  //Desliga o Heater
        pwmSet2(0);         //Desliga o Buzze
        pwmSet1(0);         //Desliga o Cooler
        PORTD = 0;          //Desliga os LEDs do PORTD
        PORTB = 0;          //Desliga os LEDs do PORTB
        PORTCbits.RC0 = 0;  //Desliga o relay 1
        PORTEbits.RE0 = 0;  //Desliga o relay 2
        lcdPosition(0, 0);
        lcdStr("Secador OFF");
        lcdPosition(1, 0);
        lcdStr("Pressione 1");
        lcdPosition(2, 0);
        lcdStr("                ");
        lcdPosition(3, 0);
        lcdStr("                ");
        //Espera input do usuário para ligar
        while (1) {
            kpDebounce();
            tecla = kpRead();
            if (bitTst(tecla, 3)) { //Enquanto não pressionar 1, o loop continua
                break;
            }
        }
        //Configurações para ligar o secador
        PORTD = 1;
        lcdPosition(0, 0);
        lcdStr("Velocity:1      ");
        lcdPosition(1, 0);
        lcdStr("Heat:OFF        ");
        lcdPosition(2, 0);
        lcdStr("Modo:Padrao  ");
        lcdPosition(3, 0);
        lcdStr("0 para desligar");
        pwmSet1(32);
        pwmSet2(50);
        //Funcionamento do secador
        while (1) {
            kpDebounce();
            if (kpRead() != tecla) {
                tecla = kpRead();
                if (bitTst(tecla, 3)) { //Tecla 1 - Velocidade de rotação lenta
                    lcdPosition(0, 9);
                    lcdStr("1");
                    pwmSet1(32);
                    PORTD = 0b10000000;
                }
                if (bitTst(tecla, 7)) { //Tecla 2 - Velocidade de rotação média
                    lcdPosition(0, 9);
                    lcdStr("2");
                    pwmSet1(67);
                    PORTD = 0b11000000;
                }
                if (bitTst(tecla, 11)) { //Tecla 3 - Velocidade de rotação alta
                    lcdPosition(0, 9);
                    lcdStr("3");
                    pwmSet1(99);
                    PORTD = 0b11100000;
                }
                if (bitTst(tecla, 2)) { //Tecla 4 - Aquecedor desliga
                    lcdPosition(1, 5);
                    lcdStr("OFF");
                    PORTCbits.RC5 = 0;
                    PORTB = 0x00;
                }
                if (bitTst(tecla, 6)) { //Tecla 5 - Aquecedor liga
                    lcdPosition(1, 5);
                    lcdStr("ON ");
                    PORTCbits.RC5 = 1;
                    PORTB = 0xF0;
                }
                if (bitTst(tecla, 1)) { //Tecla 7 - Modo de vento padrão
                    lcdPosition(2, 5);
                    lcdStr("Padrao     ");
                    PORTCbits.RC0 = 0;
                    PORTEbits.RE0 = 0;
                    pwmSet2(50);
                }
                if (bitTst(tecla, 5)) { //Tecla 8 - Modo de vento focado
                    lcdPosition(2, 5);
                    lcdStr("Focado    ");
                    PORTCbits.RC0 = 1;
                    PORTEbits.RE0 = 0;
                    pwmSet2(50);
                }
                if (bitTst(tecla, 9)) { //Tecla 9 - Modo de operação silencioso
                    lcdPosition(2, 5);
                    lcdStr("Silencioso");
                    PORTCbits.RC0 = 1;
                    PORTEbits.RE0 = 1;
                    pwmSet2(0);
                }
                if (bitTst(tecla, 4)) { //Tecla 0 - Desliga o aparelho
                    break;
                }
            }
        }
    }
}