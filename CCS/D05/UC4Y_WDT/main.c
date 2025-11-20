#include <msp430.h>

char P2OUT_tmp, P2DIR_tmp;
int state = 1;                              // Start from second iteration
int i;

void main(void) {
  // Timer mode with SMCLK and WDTI=8192
  WDTCTL = WDTPW + WDTTMSEL + WDTIS0;
  
  P2SEL &= ~(BIT7 + BIT6);
  P2SEL2 &= ~(BIT7 + BIT6);
  
  P1DIR &= ~(BIT5 + BIT4);
  P1OUT |= BIT5 + BIT4;
  P1REN |= BIT5 + BIT4;
  
  // Set initial state of LEDs
  P2DIR_tmp = 0b11001100;
  P2OUT_tmp = 0b01010101;
  
  IE1 |= WDTIE;
  IFG1 &= ~WDTIFG;

  i = 233;
  
  _BIS_SR(CPUOFF+GIE);
}

#pragma vector=WDT_VECTOR
__interrupt void My_WDT(void) {
  IFG1 &= ~WDTIFG;

  if (i > 0) {
    i--;
  } else {
    i = 233; 

    switch(state) {                         // Checks which state LEDs are in
      case 0:
        P2DIR_tmp = 0b11001100;
        P2OUT_tmp = 0b01010101;
        break;
      case 1:
        P2DIR_tmp = 0b11111111;
        break;
      case 2:
        P2DIR_tmp = 0b11001100;
        P2OUT_tmp = 0b10011001;
        break;
      case 3:
        P2DIR_tmp = 0b11111111;
        break;
    }

    state++;

    if (state > 3) {
      state = 0;
    }
  }

  switch (P1IN & (BIT5 + BIT4)) {           // Check button state
    case (0b00110000):
      P2DIR = P2DIR_tmp;
      P2OUT = P2OUT_tmp;
      break;
    case (0b00100000):
      P2DIR = P2DIR_tmp | 0b11000011;
      P2OUT = P2OUT_tmp | 0b11000011;
      break;
    case (0b00010000):
      P2DIR = P2DIR_tmp & 0b11000011;
      P2OUT = P2OUT_tmp;
      break;
    case (0b00000000):
      P2DIR = 0b11000011;
      P2OUT = 0b11000011;
      break;
  }

}