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

void spi_init(void);
int spi_rw(int data);
void spi_rw_n(uint8_t *send, uint8_t *receive, int num_bytes, int channel);

#endif 