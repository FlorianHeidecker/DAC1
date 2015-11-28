/**
 * @file	global.h
 *
 * @brief	Global Definitions for whole project
 *
 *
 * @author	Sebastian Wolfarth
 * @date	12.11.2015 - initial version
 *
 * @version	0.1
 *
 */
#include <xc.h>
#include <stdint.h>


#ifndef GLOBAL_H
#define	GLOBAL_H


/* Device dependend devines*/
#define CPU_FREQUENCY       7370000UL   /* 7.37 MHz*/
#define BAUDRATE            115200UL    /* 115,2 k*/


//==============================================================================
// Defines of GPIOs
//==============================================================================

/* SPI */
#define SCLK_TRIS           TRISBbits.TRISB7
#define SCLK_LATCH          LATBbits.LATB7

#define MISO_TRIS           TRISBbits.TRISB6
#define MISO_LATCH          LATBbits.LATB6

#define MOSI_TRIS           TRISBbits.TRISB5
#define MOSI_LATCH          LATBbits.LATB5

/* DAC */
#define DAC_MUTE_TRIS       TRISAbits.TRISA4
#define DAC_MUTE_LATCH      LATAbits.LATA4
#define DAC_MUTE_PORT       PORTAbits.RA4

#define DAC_CS_TRIS         TRISAbits.TRISA9
#define DAC_CS_LATCH        LATAbits.LATA9
#define DAC_CS_PORT         PORTAbits.RA9

/* SRC */
#define SRC_CS_TRIS         TRISBbits.TRISB8
#define SRC_CS_LATCH        LATBbits.LATB9
#define SRC_CS_PORT         PORTBbits.RB9

#define SRC_INT_TRIS        TRISCbits.TRISC5
#define SRC_INT_LATCH       LATCbits.LATC5
#define SRC_INT_PORT        PORTCbits.RC5

/* Rotary Encoder */
#define DEC_CHA_TRIS        TRISBbits.TRISB11
#define DEC_CHA_LATCH       LATBbits.LATB11
#define DEC_CHA_PORT        PORTBbits.RB11

#define DEC_CHB_TRIS        TRISBbits.TRISB12
#define DEC_CHB_LATCH       LATBbits.LATB12
#define DEC_CHB_PORT        PORTBbits.RB12

#define DEC_TASTE_TRIS      TRISBbits.TRISB13
#define DEC_TASTE_LATCH     LATBbits.LATB13
#define DEC_TASTE_PORT      PORTBbits.RB13

/* LCD */
#define LCD_RW_TRIS         TRISBbits.TRISB3
#define LCD_RW_LATCH        LATBbits.LATB3
#define LCD_RW_PORT         PORTBbits.RB3

#define LCD_EN_TRIS         TRISCbits.TRISC0
#define LCD_EN_LATCH        LATCbits.LATC0
#define LCD_EN_PORT         PORTCbits.RC0

#define LCD_RS_TRIS         TRISBbits.TRISB2
#define LCD_RS_LATCH        LATBbits.LATB2
#define LCD_RS_PORT         PORTBbits.RB2

#define LCD_DATA_TRIS       TRISA
#define LCD_DATA_LATCH      LATB
#define LCD_DATA_PORT       PORTA

/* PLL */
#define PLL_CSEL_TRIS         TRISBbits.TRISB9
#define PLL_CSEL_LATCH        LATBbits.LATB9

#define PLL_SR_TRIS         TRISCbits.TRISC6
#define PLL_SR_LATCH        LATCbits.LATC6

#define PLL_FS1_TRIS        TRISCbits.TRISC8
#define PLL_FS1_LATCH       LATCbits.LATC8

#define PLL_FS2_TRIS        TRISCbits.TRISC7
#define PLL_FS2_LATCH       LATCbits.LATC7

/* UART */
#define UART_TX_TRIS        TRISBbits.TRISB14
#define UART_TX_LATCH       LATBbits.LATB14

#define UART_RX_TRIS        TRISBbits.TRISB15
#define UART_RX_LATCH       LATBbits.LATB15

/*******************************************************************************
	Makros for bit operations
*******************************************************************************/
/** Clears a bit */
#define ClrBit(port,bit)		(port &= ~(1<<bit))
/**  sets a bit */
#define SetBit(port,bit)		(port |= (1<<bit))
/** toggles a bit */
#define ToggleBit(port,bit)		(port ^= (1<<bit))
/** Checks a bit if set */
#define BitIsSet(port,bit)		(port & (1<<bit))
/** Checks a bit if clear */
#define BitIsClr(port,bit)		(!(port & (1<<bit)))

#endif	/* GLOBAL_H */

