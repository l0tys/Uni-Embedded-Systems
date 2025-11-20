#include <msp430.h>

int i;
int state = 1;                              // Start from second iteration

void main(void) {
  // Timer mode with SMCLK and WDTI=8192
  WDTCTL = WDTPW + WDTTMSEL + WDTIS0 + WDTCNTCL;

  P2SEL &= ~(BIT7 + BIT6);
  P2SEL2 &= ~(BIT7 + BIT6);

  // Set initial state of LEDs
  P2DIR = 0b11001100;
  P2OUT = 0b01010101;

  IE1 |= WDTIE;                             // Enable WDT interrupts
  IFG1 &= ~WDTIFG;                          // Avoid dummy interrupt

  i = 233;
  
  _BIS_SR(CPUOFF+GIE);
}

#pragma vector=WDT_VECTOR
__interrupt void My_WDT(void) {
  IFG1 &= ~WDTIFG;                          // Avoid dummy interrupt

  if (i > 0) {
    i--;
  } else {
    i = 233;

    switch(state) {                         // Checks which state LEDs are in
      case 0:
        P2DIR = 0b11001100;
        P2OUT = 0b01010101;
        break;
      case 1:
        P2DIR = 0b11111111;
        break;
      case 2:
        P2DIR = 0b11001100;
        P2OUT = 0b10011001;
        break;
      case 3:
        P2DIR = 0b11111111;
        break;
    }

    state++;

    if (state > 3) {
      state = 0;
    }
  }
}