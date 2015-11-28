/*
 * File:   main.c
 * Author: Sebastian
 *
 * Created on 29. Oktober 2015, 15:31
 */



#include <xc.h>
#include <stdio.h>

#include "log.h"
#include "PLL_API.h"
#include "xlcd/xlcd.h"


int main(void) {
    LOG("main()\n");
    
    OpenXLCD(FOUR_BIT & LINES_5X7);
    
    while(BusyXLCD());
    WriteCmdXLCD(XLCD_CLR_DISP);
    
    while(BusyXLCD());
    WriteCmdXLCD(XLCD_JUMP_HOME);
    
    
    while(BusyXLCD());
    WriteCmdXLCD(SHIFT_CUR_RIGHT);

    while(BusyXLCD());
    WriteCmdXLCD(DON & CURSOR_OFF & BLINK_OFF); 
	
    while(BusyXLCD());
    WriteCmdXLCD(0b00000010);   // line 1 pos 1

    while(BusyXLCD());
    putrsXLCD("Welcome");
    
    pll_init();
    
    
    return 0;
}