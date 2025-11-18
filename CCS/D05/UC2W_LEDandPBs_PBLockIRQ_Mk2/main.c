#include <msp430.h>

char P1LOCK;

void main(void) {
  WDTCTL = WDTPW | WDTHOLD;

  P2SEL &= ~(BIT7 + BIT6);
  P2SEL2 &= ~(BIT7 + BIT6);

  P1DIR &= ~(BIT5 + BIT4);
  P1OUT |= BIT5 + BIT4;
  P1REN |= BIT5 + BIT4;
  
  P1IE = BIT5 + BIT4;
  P1IES = BIT5 + BIT4;
  P1IFG = 0b00000000;

  P1LOCK = 0b00000000;
  
  P2DIR = 0b11001100;
  P2OUT = 0b01010101;

  _bis_SR_register(GIE + CPUOFF);
}

#pragma vector=PORT1_VECTOR
__interrupt void PB4_PB5_function(void) {
  P1LOCK ^= (P1IFG & (BIT5 + BIT4));

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
  
  _delay_cycles(200000);

  P1IFG &= ~(BIT5 + BIT4);
}