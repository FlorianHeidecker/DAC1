/** 
 * @file	SPI_API.c
 *
 * @brief	SPI_API contains the basic functions to use the spi bus
 *
 * This module implements the basic functions to work with spi bus. It contains
 * a init function to startup the spi interface. For communication there a two
 * functions implemented to send/receive one or more data bytes.
 * 
 * @author	Marco Jost
 * @date	03.12.2015 - initial version
 *
 * @version	0.1
 */

#include <xc.h>

#include "log.h"
#include "global.h"
#include "SPI_API.h"
#include <libpic30.h>

void spi_init(void){
    SCLK_TRIS = 0;
    MOSI_TRIS = 0;
    SRC_CS_TRIS = 0;
    DAC_CS_TRIS = 0;
    MISO_TRIS = 1;  
    SRC_CS_LATCH = 1;
    DAC_CS_LATCH = 1;
    

    RPINR20bits.SDI1R = 5;  //Map MISO to Port 5 (Input)
    RPOR3bits.RP6R = 7;     //Map MOSI to Port 6 (Output)
    RPOR3bits.RP7R = 8;     //Map CLK to Port 7 (Output)

    
    SPI1CON1bits.DISSCK = 0; // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE = 1; // Serial output data changes on transition from
    // Idle clock state to active clock state
    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level; 
    // active state is a high level
    SPI1STATbits.SPIROV = 0; //clear the receive overflow flag, refer to master mode setup procedure
    SPI1CON1bits.PPRE = 2;  //primary prescaler
    SPI1CON1bits.SPRE = 7;  //secondary prescaler
    
    SPI1STATbits.SPIEN = 1; // Enable SPI module

}

int spi_rw(int data){
    SPI1BUF = data;
    while(!SPI1STATbits.SPIRBF);
    return SPI1BUF;
}

void spi_rw_n(uint8_t *send, uint8_t *receive, int num_bytes, SPI_channel_select_t SPI_channel)
{
    int n;
    switch (SPI_channel){
            case SPI_SRC_channel:
                SRC_CS_LATCH = 0;
                for (n = 0; n<num_bytes; n++){
                    *receive++ = spi_rw(*send++);
                }
                SRC_CS_LATCH = 1;
                break;
            case SPI_DAC_channel:
                DAC_CS_LATCH = 0;
                for (n = 0; n<num_bytes; n++){
                    *receive++ = spi_rw(*send++);
                 //   __delay_ms(10);
                }
                DAC_CS_LATCH = 1;
                break;
    }
}  
