/*
 * File:   xlcd_goto.c
 * Author: Sebastian
 *
 * Created on 2. Dezember 2015, 15:51
 */


#include <xc.h>
#include "../log.h"
#include "xlcd.h"
#include "../global.h"


void xlcd_init(void)
{
    OpenXLCD(FOUR_BIT & LINES_5X7);
    
    while(BusyXLCD());
    WriteCmdXLCD(XLCD_CLR_DISP);
    
    while(BusyXLCD());
    WriteCmdXLCD(XLCD_JUMP_HOME);

    while(BusyXLCD());
    WriteCmdXLCD(DON & CURSOR_OFF & BLINK_OFF); 
}



void xlcd_goto(uint16_t line, uint16_t elem)
{
    //uint8_t row;
    if(elem > 19)
    {
        elem = 0;
        XLCD_LOG("XLCD: xlcd_goto() %i is unsuported elem", elem);
    }
    
    switch(line)
    {
        case 0:
            line = XLCD_ROW1;
            break;
        case 1:
            line = XLCD_ROW2;
            break;
        case 2:
            line = XLCD_ROW3;
            break;
        case 3:
            line = XLCD_ROW4;
            break;
        default:
            XLCD_LOG("XLCD: xlcd_goto() %i is unsuported line", line);
            break;
    }
    
    while(BusyXLCD());
    WriteCmdXLCD(line + elem);
}




void xlcd_clear_line(uint16_t line)
{
    int i;
    if(line > 3)
    {
        XLCD_LOG("XLCD: xlcd_clear_line() %i line not supported", line);
        return;
    }
    
    xlcd_goto(line, 0);
    for(i=0; i<20; i++)
    {
        putsXLCD(" ");
    }
}


void xlcd_clear(void)
{
    while(BusyXLCD());
    WriteCmdXLCD(XLCD_CLR_DISP);
    
    while(BusyXLCD());
    WriteCmdXLCD(XLCD_JUMP_HOME);
}


void xlcd_test(void)
{
    xlcd_goto(0,0);
    putrsXLCD("1111111111111111111");

    xlcd_goto(1,0);
    putrsXLCD("2222222222222222222");

    
    xlcd_goto(2,0);
    putrsXLCD("3333333333333333333");
    
    xlcd_goto(3,0);
    putrsXLCD("4444444444444444444");
    
    xlcd_clear_line(0);
    xlcd_clear_line(1);
    xlcd_clear_line(2);
    xlcd_clear_line(3);
}