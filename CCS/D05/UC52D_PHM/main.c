#include <msp430.h>
void main(void) {
  // Stop watchdog
  WDTCTL = WDTPW + WDTHOLD;
  
  // Setup IOs
  P2DIR |= 0b00000011;
  P2SEL |= 0b00000011;
  P2SEL2 &= 0b11111100;

  TA1CCTL0 = 0;
  TA1CCTL1 = 0;

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
  
  // Start TA1 in IP mode with ACLK
  TA1CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;
  // TA period is 3s
  TA1CCR0 = 23438;
  // Setup TA1 data module CCR0
  TA1CCTL0 = OUTMOD_4;
  
  // Setup TA1 data module CCR1
  TA1CCTL1 = OUTMOD_4;
  TA1CCR1 = 23438;
  TA1CCTL0 |= CCIE;
  
  // Sleep mode with TA1 CCR1 interrupts
  _BIS_SR(GIE + CPUOFF);
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA1CCR0_isr(void) {
  TA1CCTL0 &= ~CCIFG;
  switch (P1IN & 0b00110000) {
    case 0b00110000:
      TA1CCR1 = 23438;        // for D=0%
      break;
    case 0b00100000:
      TA1CCR1 = 23438-7969;   // for D=17%
      break;
    case 0b00010000:
      TA1CCR1 = 23438-15938;  // for D=34%
      break;
    case 0b00000000:
      TA1CCR1 = 23438-23038;  // for D=50%
      break;
  }
}