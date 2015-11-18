/*
 * File:   main.c
 * Author: Sebastian
 *
 * Created on 29. Oktober 2015, 15:31
 */

#include <xc.h>
#include <stdio.h>

#include "log.h"
#include "xlcd.h"
#include "PLL_API.h"


int main(void) {
    LOG("main()\n");
    
    pll_init();
    
	while(1);
    return 0;
	
}