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
    
    set_setting(0,1,2); // change setting to off
    
	while(1);
    return 0;
	
}