/* 
 * File:   UART_API.h
 * Author: Marco Jost
 * Comments:
 * Revision history:  1.0
 */

#include <xc.h>
#include "global.h" 

#ifndef _UART_API_H
#define _UART_API_H


void uart_init(void);
void uart_send_char(char data);
void uart_send_string(char *str);

#endif 