/*
 * File:   main.c
 * Author: Sebastian
 *
 * Created on 29. Oktober 2015, 15:31
 */

 #define FOSC    (7370000UL)
 #define FCY     (FOSC/2)

#include <xc.h>
#include <stdio.h>

#include "log.h"
#include "PLL_API.h"
#include "xlcd/xlcd.h"


int main(void) {
    LOG("main()\n");
    
    OpenXLCD(FOUR_BIT & LINES_5X7);
    
    while(BusyXLCD() );
    WriteCmdXLCD(SHIFT_CUR_RIGHT);

    while(BusyXLCD() );
    WriteCmdXLCD(DON & CURSOR_OFF & BLINK_OFF); 
	
    while(BusyXLCD() );
    WriteCmdXLCD(0b00000010);   // line 1 pos 1

    while( BusyXLCD() );
    putrsXLCD("Welcome");
    
    pll_init();
    
    
    return 0;
}