#include <msp430.h>
void main(void) {
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR = 0b01000001;
  P1OUT = 0b01000001;
  
  // Low frequency mode of LFXT1
  BCSCTL1 &= ~XTS;
  // Turn on LFXT1 (32.768kHz crystal)
  BCSCTL3 &= ~(LFXT1S1 | LFXT1S0);
  
  // 2^DIVA=1 -> no ACLK divider
  BCSCTL1 &= ~(DIVA1 | DIVA0);
  
  // Wait for LFXT1 to stabilize
  _BIC_SR(OSCOFF);
  while (IFG1 & OFIFG) {
    IFG1 &= ~OFIFG;
    __delay_cycles(10000);
  }
  
  // Start TA0 in CONTINUOUS mode with ACLK
  TA0CTL = TASSEL_1 + ID_2 + MC_2 + TACLR;
  TA0CCR0 = 10714;
  TA0CCTL0 = CCIE;
  
  // Start TA1 in CONTINUOUS mode with ACLK
  TA1CTL = TASSEL_1 + ID_2 + MC_2 + TACLR;
  TA1CCR0 = 5000;
  TA1CCTL0 = CCIE;
  
  _BIS_SR(GIE+CPUOFF);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0CCR0_isr(void) {
  TA0CCR0 += 10714;
  TA0CCTL0 &= ~CCIFG;
  P1OUT ^= BIT6;
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA1CCR0_isr(void) {
  TA0CCR1 += 5000;
  TA0CCTL1 &= ~CCIFG;
  P1OUT ^= BIT0;
}