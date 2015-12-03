/** 
 * File:   SPI_API.h
 * Author: Marco Jost
 * Comments:
 * Revision history:  1.0
 */

#include <xc.h>
#include "global.h" 

#ifndef _SPI_API_H
#define _SPI_API_H

#define READ_WRITE_DAC 0x8000
#define READ_WRITE_SRC 0x0080

void spi_init(void);
int spi_rw(int data);
int spi_src(int header, int data);
int spi_dac(int data);


#endif 