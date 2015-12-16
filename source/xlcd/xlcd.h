#ifndef __XLCD_H
#define __XLCD_H
#include <xc.h>

#include "../global.h"
/* PIC18 XLCD peripheral routines.
 *
 *   Notes:
 *      - These libraries routines are written to support the
 *        Hitachi HD44780 LCD controller.
 *      - The user must define the following items:
 *          - The LCD interface type (4- or 8-bits)
 *          - If 4-bit mode
 *              - whether using the upper or lower nibble
 *          - The data port
 *              - The tris register for data port
 *              - The control signal ports and pins
 *              - The control signal port tris and pins
 *          - The user must provide three delay routines:
 *              - DelayFor18TCY() provides a 18 Tcy delay
 *              - DelayPORXLCD() provides at least 15ms delay
 *              - DelayXLCD() provides at least 5ms delay
 */

/* Interface type 8-bit or 4-bit
 * For 8-bit operation uncomment the #define BIT8
 */
/* #define BIT8 */

/* When in 4-bit interface define if the data is in the upper
 * or lower nibble.  For lower nibble, comment the #define UPPER
 */
/* #define UPPER */

/* DATA_PORT defines the port to which the LCD data lines are connected */
 #define DATA_PORT      		LCD_DATA_PORT
 #define TRIS_DATA_PORT 		LCD_DATA_TRIS

/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
 #define RW_PIN   LCD_RW_LATCH   		/* PORT for RW */
 #define TRIS_RW  LCD_RW_TRIS    	/* TRIS for RW */

 #define RS_PIN   LCD_RS_LATCH   		/* PORT for RS */
 #define TRIS_RS  LCD_RS_TRIS    	/* TRIS for RS */

 #define E_PIN    LCD_EN_LATCH  		/* PORT for D  */
 #define TRIS_E   LCD_EN_TRIS    	/* TRIS for E  */

/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */

/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00000100  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00000101  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00000110  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00000111  /* Display shifts to the right */

#define XLCD_JUMP_HOME      0b00000010  /* Jump to homeposition (Line1, Pos1) */
#define XLCD_CLR_DISP       0b00000001  /* Clear Display */


/* Function Set defines */
#define FOUR_BIT   0b00101100  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111100  /* 8-bit Interface               */

#define LINE_5X7   0b00110000  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110100  /* 5x10 characters               */
#define LINES_5X7  0b00111000  /* 5x7 characters, multiple line */

#define XLCD_ROW1        0x80   //0x80 + 0
#define XLCD_ROW2        0xC0   //0xc0 + 0
#define XLCD_ROW3        0x94   //0x80 + 20 
#define XLCD_ROW4        0xD4   //0xC0 + 20


#define _OMNI_CODE_

#ifdef _OMNI_CODE_
#define PARAM_SCLASS
#else
#define PARAM_SCLASS auto
#endif

#ifndef MEM_MODEL
#ifdef _OMNI_CODE_
#define MEM_MODEL
#else
#define MEM_MODEL far  /* Change this to near for small memory model */
#endif
#endif

/* OpenXLCD
 * Configures I/O pins for external LCD
 */
void OpenXLCD(PARAM_SCLASS unsigned char);

/* SetCGRamAddr
 * Sets the character generator address
 */
void SetCGRamAddr(PARAM_SCLASS unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */
void SetDDRamAddr(PARAM_SCLASS unsigned char);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
unsigned char BusyXLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
unsigned char ReadAddrXLCD(void);

/* ReadDataXLCD
 * Reads a byte of data
 */
char ReadDataXLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */
void WriteCmdXLCD(PARAM_SCLASS unsigned char);

/* WriteDataXLCD
 * Writes a data byte to the LCD
 */
void WriteDataXLCD(PARAM_SCLASS char);

/* putcXLCD
 * A putc is a write
 */
#define putcXLCD WriteDataXLCD

/* putsXLCD
 * Writes a string of characters to the LCD
 */
void putsXLCD(PARAM_SCLASS char *);

/* putrsXLCD
 * Writes a string of characters in ROM to the LCD
 */
void putrsXLCD(const char *);

/* User defines these routines according to the oscillator frequency */
extern void DelayFor18TCY(void);
extern void DelayPORXLCD(void);
extern void DelayXLCD(void);

/** Sets cursor to a line and an element
 * 
 * @param line  Line to set 0..3
 * @param elem  Element in line to set 0..19
 */
void xlcd_goto(uint16_t line, uint16_t elem);

/** Clears a line on display
 * 
 * @param line  Line to clear 0..3
 */
void xlcd_clear_line(uint16_t line);


/** Initialzes XLCD
 * 
 */
void xlcd_init(void);

/** Clears complete display
 * 
 */
void xlcd_clear(void);

#endif
