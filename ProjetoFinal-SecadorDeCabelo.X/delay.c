#include "delay.h"

void atraso_ms(unsigned int t) {
    volatile unsigned char j, k;
    volatile unsigned int i;
    for (i = 0; i < t; i++) {        
        for (j = 0; j < 41; j++) {
            for (k = 0; k < 3; k++);
        }
    }
}

// Mesclando ms e s pra tentar dar mais precisao no tempo
void atraso_s(unsigned int t) {
    volatile unsigned char j, k;
    volatile unsigned int i;
    for (i = 0; i < (t * 1000); i++) {        
        for (j = 0; j < 41; j++) {
            for (k = 0; k < 3; k++);
        }
    }
}

/* void atraso_s(unsigned int t) {
    volatile unsigned char j, k;
    volatile unsigned int i, s;
    for(s = 0; s < t; s++) {
        for (i = 0; i < 1000; i++) {        
            for (j = 0; j < 41; j++) {
                for (k = 0; k < 3; k++);
            }
        }
    }
} */