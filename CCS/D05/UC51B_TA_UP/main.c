#include <msp430.h>

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0b01000001;
  P1OUT = 0b01000001;

  // Low frequency mode of LFXT1
  BCSCTL1 &= ~XTS;
  BCSCTL3 &= ~LFXT1S0;
  BCSCTL3 |= LFXT1S1;
  // 2^DIVA=2^0=1 -> f_ACKL = f_LFXT1 / 1 T_aclk=2*T_LFXT1
  BCSCTL1 &= ~(DIVA1 | DIVA0); 

  _BIC_SR(OSCOFF);

  while (IFG1 & OFIFG) {
    IFG1 &= ~OFIFG;
    _delay_cycles(10000);
  }

  // Start TA0 in up mode with T_TAclk=4T_aclk
  TA0CTL = TASSEL_1 + ID_2 + MC_1 + TACLR;
  // Eanble interrupts at TA0R = TA0CCR0
  TA0CCR0 = 4500;
  TA0CCTL0 = CCIE;

  // Start TA1 in up mode with T_TAclk=4T_aclk
  TA1CTL = TASSEL_1 + ID_2 + MC_1 + TACLR;
  // Eanble interrupts at TA1R = TA1CCR0
  TA1CCR0 = 2100;
  TA1CCTL0 = CCIE;

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
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA1CCR0_isr(void) {
  // Toggle GREEN LED
  P1OUT ^= BIT0;
}
