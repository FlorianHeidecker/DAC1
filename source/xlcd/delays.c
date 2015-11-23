/*
 * File:   delays.c
 * Author: Sebastian
 *
 * Created on 23. November 2015, 20:10
 */

#define FCY     (700000/2)

#include <xc.h>
#include "delays.h"


void DelayFor18TCY (void)
{
   char k = 0;

   for( k=0; k<18; k++)
   {
       asm("nop\n\t");
      //__nop();
   }
}
void DelayPORXLCD (void)
{
   //__delay_ms(15);
}

void DelayXLCD (void)
{
   //__delay_ms(5);
}


void Delay10KTCYx(unsigned char delay)
{
    
}

