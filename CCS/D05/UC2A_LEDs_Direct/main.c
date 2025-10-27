#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P2SEL = 0b00000000;

    for (;;) {
        P2DIR = 0b11001100;
        P2OUT = 0b01010101;
        _delay_cycles(2000000);

        P2DIR = 0b11111111;
        _delay_cycles(2000000);

        P2DIR = 0b11001100;
        P2OUT = 0b10011001;
        _delay_cycles(2000000);

        P2DIR = 0b11111111;
        _delay_cycles(2000000);
    }
}