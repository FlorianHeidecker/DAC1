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
    
    pll_init();
    
    
    return 0;
}