/*
* File:   SPI_API.c
* Author: Marco Jost
* Comments:  This Module implements the SPI API. The Module contains functions for initialization and sending data over SPI
* Revision history:  1.0
*/

#include <xc.h>


#include "log.h"
#include "global.h"
#include "SPI_API.h"

void spi_init(void){
    
    SCLK_TRIS = 0;
    MOSI_TRIS = 0;
    SRC_CS_TRIS = 0;
    DAC_CS_TRIS = 0;
    MISO_TRIS = 1;  
    SRC_CS_LATCH = 1;
    DAC_CS_LATCH = 1;
    
    RPINR20bits.SDI1R = 6;  //Map MISO to Port 6 (Input)
    RPOR2bits.RP5R = 7;     //Map MOSI to Port 5 (Output)
    RPOR3bits.RP7R = 8;     //Map CLK to Port 7 (Output)

    
    SPI1CON1bits.DISSCK = 0; // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE = 0; // Serial output data changes on transition from
    // Idle clock state to active clock state
    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level; 
    // active state is a high level
    SPI1STATbits.SPIROV = 0; //clear the receive overflow flag, refer to master mode setup procedure
    SPI1STATbits.SPIEN = 1; // Enable SPI module
    SPI1CON1bits.PPRE = 3;  //primary prescaler
    SPI1CON1bits.SPRE = 7;  //secondary prescaler


}

int spi_rw(int data){
    SPI1BUF = data;
    while(!SPI1STATbits.SPIRBF);
    return SPI1BUF;
}

int spi_rw_n(uint8_t *send, uint8_t *receive, int num_bytes, int channel)
{
    
    return 0;
}



int spi_src(int header, int data){
    int temp;
    
    SRC_CS_LATCH = 0;
    if(header & READ_WRITE_SRC){
        temp = spi_rw(header);
        temp = spi_rw(0);
    }
    else{
        temp = spi_rw(header);
        temp = spi_rw(data);
        temp = 0;
    }
    SRC_CS_LATCH = 1;
    return temp;
}


int spi_dac(int data){
    
    int temp;
    
    DAC_CS_LATCH = 0;
    if(data & READ_WRITE_DAC){
        temp = spi_rw(data);
    }
    else{
        temp = spi_rw(data);
        temp = 0;
    }
    DAC_CS_LATCH = 1;
    return temp;
}

