/** 
 * @file	SPI_API.h
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
#include "global.h" 

#ifndef _SPI_API_H
#define _SPI_API_H

enum{SPI_SRC_channel, SPI_DAC_channel};



/** @brief Init function for spi
 *
 *  This function initializes the spi bus
 * 
 */
void spi_init(void);


/** @brief Read/write function for spi
 *
 *  This function reads and writes simultaneously one byte from spi bus
 *  
 * @param data  data to send 
 * @return      return the received data
 */
int spi_rw(int data);


/** @brief Read/write function for spi
 *
 *  This function reads and writes simultaneously a variable number of bytes from spi bus
 *  
 * @param *send     pointer on data to send 
 * @param *receive  pointer on data to receive 
 * @param num_btes  number of data bytes 
 * @param channel   Channel to select betwenn SRC and DAC chip select
 */
void spi_rw_n(uint8_t *send, uint8_t *receive, int num_bytes, int channel);

#endif 