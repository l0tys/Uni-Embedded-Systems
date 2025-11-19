#include <msp430.h>

void main(void) {
  WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL;     

  P1DIR |= BIT6 + BIT0;                     // Enable LEDs
  P1OUT |= BIT6;                            // Green LED on
  P1OUT &= ~BIT0;                           // Red LED off

  DCOCTL = 0 * 32;                          // DCO = 0 w/o modulation
  BCSCTL1 = (BCSCTL1 & 0b11110000) | RSEL1; // Force RSEL=2
  BCSCTL2 |= DIVS0;                         // T_SMCLK=2xT_DCO

  IE1 |= WDTIE;                             // Enable WDT interrupts
  IFG1 &= ~WDTIFG;                          // Avoid dummy interrupt

  _BIS_SR(CPUOFF+GIE);
}

#pragma vector=WDT_VECTOR
__interrupt void My_WDT(void) {
  IFG1 &= ~WDTIFG;                          // Avoid dummy interrupt
  P1OUT ^= (BIT6 + BIT0);                   // Toggle both LEDs
}