#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P2SEL &= ~(BIT7 + BIT6);
    P2SEL2 &= ~(BIT7 + BIT6);

    for (;;) {
        P2DIR = 0b11001100;
        P2OUT = 0b01010101;
        Delay();

        P2DIR = 0b11111111;
        Delay();

        P2DIR = 0b11001100;
        P2OUT = 0b10011001;
        Delay();

        P2DIR = 0b11111111;
        Delay();
    }
}

void Delay(void) {
    _delay_cycles(2000000);
}