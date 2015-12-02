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
    for(i=0; i<19; i++)
    {
        putsXLCD(" ");
    }
}