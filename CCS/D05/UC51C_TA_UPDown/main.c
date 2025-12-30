#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;
    
    P1DIR = 0b01000001;
    P1OUT = 0b01000000;
    
    BCSCTL1 = 0b10000000;  
    DCOCTL = 0b00000000;   
    BCSCTL2 = 0;         
    
    TA0CTL = TASSEL_2 + ID_2 + MC_3 + TACLR;
    TA0CCR0 = 18750;
    TA0CCTL0 = CCIE;
    
    TA1CTL = TASSEL_2 + ID_2 + MC_3 + TACLR;
    TA1CCR0 = 8750;
    TA1CCTL0 = CCIE;
    
    __enable_interrupt();
    _BIS_SR(LPM0_bits + GIE); 
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void) {
    P1OUT ^= BIT6;  
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1_ISR(void) {
    P1OUT ^= BIT0; 
}