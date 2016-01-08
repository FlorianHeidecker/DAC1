/** 
 * @file	UART_API.c
 *
 * @brief	Implementation UART
 *
 * This Module implements the UART API. The Module contains functions for 
 * initialization and sending characters
 */

#include <xc.h>

#include "log.h"
#include "global.h"
#include "UART_API.h"


void uart_init(void) {

	U1MODEbits.BRGH = 0;
	U1BRG = ((PERIPHERAL_FREQUENCY / 16 / BAUDRATE) - 1);

	UART_TX_TRIS = 0;	//Set Pin14(TX) as output
	UART_RX_TRIS = 1; //Set Pin15(RX) as (analog) input

	AD1PCFGLbits.PCFG9 = 1;	//Set RX as digital input

	RPINR18bits.U1RXR = 15; //Map RX to Pin15
	RPOR7bits.RP14R = 3; //Map TX to Pin14
	
	U1MODEbits.PDSEL0 = 0;	//8 n 1
	U1MODEbits.PDSEL1 = 0;
	U1MODEbits.STSEL = 0;

    
    U1MODEbits.UARTEN = 1; //Enable Uart1 
    while(U1MODEbits.UARTEN == 0); 
    U1STAbits.UTXEN = 1; //Enable Transmit
    while(U1STAbits.UTXEN == 0);

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