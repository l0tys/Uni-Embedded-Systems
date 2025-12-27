#include <msp430.h>

void main(void) {
  // Stop watchdog
  WDTCTL = WDTPW + WDTHOLD;
  
  // Prepare P1.6 to drive RED LED from TA0.1
  P1DIR |= 0b01000000;
  P1SEL |= 0b01000000;
  P1SEL2 &= 0b10111111;

  // Setup P1.4/5 to test PB14 and PB15
  P1DIR &= ~(BIT5 + BIT4);
  P1OUT |= BIT5 + BIT4;
  P1REN |= BIT5 + BIT4;

  // Set f DCO = 100000 Hz
  DCOCTL = 0;
  BCSCTL1 = 0;
  DCOCTL = DCO0;
  
  // 2^DIVA=1
  BCSCTL2 &= ~(DIVS_3);
  
  // Start TA0 in CONTINUOUS mode with ACLK
  TA0CTL = TASSEL_2 + ID_2 + MC_3 + TACLR;
  // TA period
  TA0CCR0 = 15000;
  
  // Setup TA0 CCR0
  TA0CCTL0 = CCIE;
  TA0CCTL1 = OUTMOD_2;
 
  // Setup TA0 CCR1
  TA0CCR1 = 7500;
  
  // Sleep mode with TA0 CCR0 interrupts
  _BIS_SR(GIE + CPUOFF);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0CCR0_isr(void) {
  // depending on PB15 and PB14 set new period
  switch (P1IN & 0b00110000) {
    case 0b00110000:
      TA0CCR0 = 15000;  // for D=50%
      break;
    case 0b00100000:
      TA0CCR0 = 22500;  // for D=33%
      break;
    case 0b00010000:
      TA0CCR0 = 30000;  // for D=25%
      break;
    case 0b00000000:
      TA0CCR0 = 37500;  // for D=20%
      break;
  }
}