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
#include "SPI_API.h"


int main(void) {
    int temp;
    AD1PCFGL = 0x1fff;
    log_init();
    LOG("main()\n");
    

    spi_init();
    while(1)
    {
    temp = spi_rw(0x5555);
    for(temp=0; temp<10000;temp++);
    }
    
    
    pll_init();


    while(1); 
    return 0;
}