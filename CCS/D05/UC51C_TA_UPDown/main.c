#include <msp430.h>

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0b01000001;
  P1OUT = 0b01000001;

  BCSCTL1 = 0b10000000;
  DCOCTL = 0b00000000;

  // 2^DIVA=2^0=1 -> f_ACKL = f_LFXT1 / 1 T_aclk=2*T_LFXT1
  BCSCTL2 &= ~(DIVA1 | DIVA0);

  // Start TA0 in up/down mode with T_TAclk=4T_aclk
  TA0CTL = TASSEL_2 + ID_2 + MC_3 + TACLR;
  // Eanble interrupts at TA0R = TA0CCR0
  TA0CCR0 = 18750;
  TA0CCTL0 = CCIE;

  // Eanble interrupts at TA1R = TA1CCR0
  TA0CCR1 = 8750;
  TA0CCTL1 = CCIE;

  // Sleep mode with TA0/TA1 CCR0 interrupts
  _BIS_SR(GIE+CPUOFF);
}

// Interrupt of CCR0 data module of TA0
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0CCR0_isr(void) {
  // Toggle RED LED
  P1OUT ^= BIT6;
}

// Interrupt of CCR0 data module of TA1
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA1CCR0_isr(void) {
  // Toggle GREEN LED
  P1OUT ^= BIT0;
}
