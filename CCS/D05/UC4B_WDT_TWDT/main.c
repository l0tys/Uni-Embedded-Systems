#include <msp430.h>

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= BIT6 + BIT0;                     // Enable LEDs
  P1OUT |= BIT6;                            // Green LED on
  P1OUT &= ~BIT0;                           // Red LED off

  DCOCTL = 1 * 32;                          // DCO = 1 w/o modulation
  BCSCTL1 |= (RSEL3 | RSEL2 | RSEL1);

  while (1) {
    P1OUT ^= (BIT6 + BIT0);                 // Toggle both LEDs
    _delay_cycles(119200000 / 2);
  }
}
