#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P2SEL = 0b00000000;

    P2DIR = 0b11001100;
    P2OUT = 0b01010101;

    for (;;) {
        _delay_cycles(2000000);

        P2DIR ^= 0b00110011;

        _delay_cycles(2000000);

        P2DIR ^= 0b00110011;
        P2OUT ^= 0b11001100;

        _delay_cycles(2000000);

        P2DIR ^= 0b00110011;

        _delay_cycles(2000000);

        P2DIR ^= 0b00110011;
        P2OUT ^= 0b11001100;
    }
}