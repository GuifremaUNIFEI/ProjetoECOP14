#ifndef TECLADO_H
#define	TECLADO_H

    #define TL1 0x01
    #define TL2 0x02
    #define TL3 0x04

    unsigned char tc_tecla(unsigned int timeout); /*timeout=0 no time out*/

#endif