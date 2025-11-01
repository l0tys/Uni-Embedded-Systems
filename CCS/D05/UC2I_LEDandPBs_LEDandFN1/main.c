#include <msp430.h>

char P2OUT_tmp, P2DIR_tmp;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P2SEL &= ~(BIT7 + BIT6);
    P2SEL2 &= ~(BIT7 + BIT6);

    P1DIR &= ~(BIT5 + BIT4);
    P1OUT |= BIT5 + BIT4;
    P1REN |= BIT5 + BIT4;

    for (;;) {
        P2DIR_tmp = 0b11001100;
        P2OUT_tmp = 0b01010101;
        Delay();

        P2DIR_tmp = 0b11111111;
        Delay();

        P2DIR_tmp = 0b11001100;
        P2OUT_tmp = 0b10011001;
        Delay();

        P2DIR_tmp = 0b11111111;
        Delay();
    }
}

void Delay(void) {
  int i;

  for (i=100; i>0; i--) {
    switch (P1IN & (BIT5 + BIT4)) {
      case (0b001100000):
        P2DIR = P2DIR_tmp;
        P2OUT = P2OUT_tmp;
        break;
      case (0b001000000):
        P2OUT = P2OUT_tmp;
        P2DIR = P2DIR_tmp & 0b00111100;
        break;
      case (0b000100000):
        P2OUT = P2OUT_tmp;
        P2DIR = P2DIR_tmp & 0b11000011;
        break;
      case (0b000000000):
        P2OUT = P2OUT_tmp;
        P2DIR = 0b00000000;
        break;
    } 
  }

  _delay_cycles(20000);
}

// void Delay(void) {
//   switch (P1IN & (BIT5 + BIT4)) {
//     case (0b001100000):
//       P2DIR = P2DIR_tmp;
//       P2OUT = P2OUT_tmp;
//       break;
//   //   case (0b001000000):
//   //     P2OUT = P2OUT_tmp;
//   //     P2DIR = P2DIR_tmp & 0b00111100;
//   //     break;
//   //   case (0b000100000):
//   //     P2OUT = P2OUT_tmp;
//   //     P2DIR = P2DIR_tmp & 0b11000011;
//   //     break;
//   //   case (0b000000000):
//   //     P2OUT = P2OUT_tmp;
//   //     P2DIR = 0b00000000;
//   //     break;
//   } 

//   _delay_cycles(2000000);
// }