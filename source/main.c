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
#include "UART_API.h"

int main(void) {
    LOG("main()\n");

    AD1PCFGL = 0x1fff;

    //=======================================
    // initalisation of the modules
    log_init();
    LOG("\n\nLOG: main()\n");
    
    LOG("LOG: xlcd_init()\n");
    xlcd_init();
    LOG("LOG: spi_init()\n");
    spi_init();
    LOG("LOG: DEC_init()\n");
    DEC_init();


    while(1); 
}