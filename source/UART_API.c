/*
* File:   UART_API.h
* Author: Marco Jost
* Comments:  This Module implements the UART API. The Module contains functions for initialization and sending characters
* Revision history:  1.0
*/

#include <xc.h>

#include "log.h"
#include "global.h"
#include "UART_API.h"


void uart_init(void) {

	U1MODEbits.BRGH = 0;
	U1BRG = ((PERIPHERAL_FREQUENCY / 16 / BAUDRATE) - 1);

	TRISBbits.TRISB14 = 0;	//Set Pin14(TX) as output
	TRISBbits.TRISB15 = 1; //Set Pin15(RX) as (analog) input

	AD1PCFGLbits.PCFG9 = 1;	//Set RX as digital input

	RPINR18bits.U1RXR = 15; //Map RX to Pin15
	RPOR7bits.RP14R = 3; //Map TX to Pin14
	
	U1MODEbits.PDSEL0 = 0;	//8 n 1
	U1MODEbits.PDSEL1 = 0;
	U1MODEbits.STSEL = 0;

	U1STAbits.UTXEN = 1; //Enable Transmit

	U1MODEbits.UARTEN = 1; //Enable Uart1
}

void uart_send_char(char data){

	while (U1STAbits.UTXBF == 1); //transmit ONLY if TX buffer is empty
	U1TXREG = data;
}

void uart_send_string(char *str)
{
    while(*str != 0)
    {
        uart_send_char(*str++);
    }
}