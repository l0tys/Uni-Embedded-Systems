#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;
    
    P1DIR = 0b01000001;
    P1OUT = 0b00000001;
    
    BCSCTL1 &= ~XTS;
    BCSCTL3 = LFXT1S_2;
    BCSCTL1 &= ~(DIVA1 | DIVA0);
    
    TA0CTL = TASSEL_1 + ID_2 + MC_1 + TACLR;
    TA0CCR0 = 4500;
    TA0CCTL0 = CCIE;
    
    TA1CTL = TASSEL_1 + ID_2 + MC_1 + TACLR;
    TA1CCR0 = 2100;
    TA1CCTL0 = CCIE;
    
    __enable_interrupt();
    _BIS_SR(LPM3_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void) {
    P1OUT ^= BIT6;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1_ISR(void) {
    P1OUT ^= BIT0;
}