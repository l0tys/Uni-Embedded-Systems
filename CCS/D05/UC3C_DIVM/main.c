#include <msp430.h>

int i;

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= BIT6 + BIT0;                     // Enable LEDs

  while (1) {
    for (i=1; i<=3; i++) {
      P1OUT &= ~(BIT6 + BIT0);              // Green & Red LED off
      BCSCTL2 &= ~(DIVM1 + DIVM0);          // fMCLK = fDCO / 1
      Delay_Cycles();
      P1OUT |= BIT6;                        // Red LED on
      BCSCTL2 |= DIVM0;                     // fMCLK = fDCO / 2
      Delay_Cycles();
    }

    for (i=1; i<=3; i++) {
      P1OUT &= ~(BIT6 + BIT0);              // Green & Red LED off
      BCSCTL2 ^= (DIVM1 + DIVM0);           // fMCLK = fDCO / 4
      Delay_Cycles();
      P1OUT |= BIT0;                        // Red LED on
      BCSCTL2 ^= (DIVM1 + DIVM0);           // fMCLK = fDCO / 2
      Delay_Cycles();
    }
  }
}

void Delay_Cycles(void) {
  _delay_cycles(1000000);
}
