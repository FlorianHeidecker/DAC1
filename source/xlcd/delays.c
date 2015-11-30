/*
 * File:   delays.c
 * Author: Sebastian
 *
 * Created on 23. November 2015, 20:10
 */

#include <xc.h>
#include "delays.h"

/* definition of typical duration of loop containg clear watchdog */
/* given in TCYs */
#define TCY_CNT_PER_LOOP 4


void DelayFor18TCY (void)
{
   char k = 0;

   for( k=0; k<18; k++)
   {
       asm("clrwdt");
      //__nop();
   }
}

//void DelayPORXLCD (void)
//{
//   __delay_ms(15);
//}

void DelayPORXLCD(void) 	/* provides delay for atleast 15msec */
{
    /* Give a delay of atleast 15 msec after power up	*/
    /* POR Power On Reset */
    
   long i;
    for(i=0;i < DelayPORXLCD_Cnt;i+=TCY_CNT_PER_LOOP)
    {
        asm("clrwdt");
    }
}

//void DelayXLCD (void)
//{
//   //__delay_ms(5);
//}

void DelayXLCD(void)  		/* provides delay for atleast 5msec */
{
  long i;
    for(i=0;i < DelayXLCD_Cnt;i+=TCY_CNT_PER_LOOP)
    {
        asm("clrwdt");
    }
}


void Delay10KTCYx(unsigned char delay)
{
    long i;
    for(i=0;i < (long)delay*10000;i+=TCY_CNT_PER_LOOP)
    {
        asm("clrwdt");
    }
}

