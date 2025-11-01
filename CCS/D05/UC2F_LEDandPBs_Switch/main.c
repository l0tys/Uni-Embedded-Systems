#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P2SEL &= ~(BIT7 + BIT6);
    P2SEL2 &= ~(BIT7 + BIT6);

    P1DIR &= ~(BIT5 + BIT4);
    P1OUT |= BIT5 + BIT4;
    P1REN |= BIT5 + BIT4;

    for (;;) {
        switch (P1IN & (BIT5 + BIT4)) {
            case (BIT5 + BIT4):
                P2DIR = 0b11001100;
                P2OUT = 0b01010101;
                break;
            case (BIT5):
                P2DIR = 0b11111111;
                P2OUT = 0b01010101;
                break;
            case (BIT4):
                P2DIR = 0b11001100;
                P2OUT = 0b10011001;
                break;
            default:
                P2DIR = 0b11111111;
                P2OUT = 0b10011001;
                break;
        }
    }
}