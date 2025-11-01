#include <msp430.h>

char P1OLD, P1NEW, P1EDGE, P1TON, P1TOFF, P1LOCK;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P2SEL &= ~(BIT7 + BIT6);
    P2SEL2 &= ~(BIT7 + BIT6);

    P1DIR &= ~(BIT5 + BIT4);
    P1OUT |= BIT5 + BIT4;
    P1REN |= BIT5 + BIT4;

    P1NEW = P1IN & (BIT5 + BIT4);
    P1OLD = P1NEW;
    
    for (;;) {
      P1OLD = P1NEW;
      P1NEW = P1IN & (BIT5 + BIT4);

      P1EDGE = P1OLD ^ P1NEW;
      P1TON = P1EDGE & P1OLD;
      P1TOFF = P1EDGE & P1NEW;

      P1LOCK = P1LOCK ^ P1TON;

      _delay_cycles(200000);

      if (P1LOCK & BIT4) {
        P2DIR = 0b11111111;
      } else {
        P2DIR = 0b11001100;
      }

      if (P1LOCK & BIT5) {
        P2OUT = 0b10011001;
      } else {
        P2OUT = 0b01010101;
      }
    }
}