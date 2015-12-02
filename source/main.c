/**
 * @file    main.c
 *
 * @brief   Main Function of DAC1 Project
 * 
 * This is the main routine of DAC1 Project.
 * 
 * @author  Sebastian Wolfarth
 * @date    29.10.15 - inital version
 * 
 * @version 0.1
 */



#include <xc.h>

#include "log.h"
#include "PLL_API.h"
#include "xlcd/xlcd.h"
#include "UART_API.h"

#include <libpic30.h>
#include <stdio.h>

int main(void) {
    AD1PCFGL = 0x1fff;
    log_init();
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
    putrsXLCD("Welcome");
    
    pll_init();



    while(1); 
}