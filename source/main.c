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
#include <stdio.h>

#include "log.h"
#include "PLL_API.h"
#include "UART_API.h"
#include "PCM_API.h"

int main(void) {
    LOG("main()\n");
    pll_init();
    pcm_init();

    while(1); 
}