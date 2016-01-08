/** 
 * @file	UART_API.h
 *
 * @brief	Implementation UART
 *
 * This Module implements the UART API. The Module contains functions for 
 * initialization and sending characters
 * 
 * @author  Marco Jost
 * @date    11.12.2011 - initial version
 * 
 * @version 0.1
 */

#include <xc.h>
#include "global.h" 

#ifndef _UART_API_H
#define _UART_API_H


void uart_init(void);
void uart_send_char(char data);
void uart_send_string(char *str);

#endif 