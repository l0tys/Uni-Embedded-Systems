#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    
    P1DIR = 0b01000001;
    P1OUT = 0b01000000;
    
    P2SEL |= BIT6 | BIT7;
    BCSCTL1 &= ~XTS;
    BCSCTL3 = XCAP_3;
    BCSCTL3 &= ~(LFXT1S1 | LFXT1S0);
    BCSCTL1 &= ~(DIVA1 | DIVA0);
    
    __bic_SR_register(OSCOFF);
    
    volatile unsigned int i;
    do {
        IFG1 &= ~OFIFG;
        for(i = 50000; i > 0; i--);
    } while (IFG1 & OFIFG);
    
    TA0CTL = TASSEL_1 + ID_2 + MC_2 + TACLR;
    TA0CCR0 = 12288;
    TA0CCTL0 = CCIE;

    TA0CCR1 = 5734;
    TA0CCTL1 = CCIE;
    
    __enable_interrupt();
    _BIS_SR(LPM3_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void) {
    TA0CCR0 += 12288;
    P1OUT ^= BIT6;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1_ISR(void) {
    TA0CCR1 += 5734;
    TA0CCTL1 &= ~CCIFG;
    P1OUT ^= BIT0;
}