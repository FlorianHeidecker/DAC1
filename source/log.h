/** 
 * @file	log.h
 *
 * @brief	Implementation of printf() like logging over UART
 *
 * This Module implements a logging functionality. It operates similar to printf.
 * Multiple Log Levels can be defined for debug purposes. By disabling
 * the logging for on group no code will be generated for this part.
 * 
 * The implementation of the output can be different depending on the device and
 * the available library functions. 
 *
 * @author	Sebastian Wolfarth
 * @date	11.12.2011 - initial version
 * @date    16.11.2015 - added stdio.h include to log.h
 *
 * @version	0.11
 *
 */

#include <stdint.h>
#include <stdio.h>

#ifndef _LOG_H
#define _LOG_H



/** Initialisation routine for the debug interface */
#define SER_INIT()		//uart1_init()
/** routine to send one char on the debug interface */
#define SER_PUTC(x)		//PutChar(x)
/** routine to send a string on the debug interface */
#define SER_PUTS(x)		//PutStr(x,1)


/** This define is set in MPLAB configuration for Simulator */
#ifdef SIMULATOR
    #define LOG_WRITE_FUNCTION(x, args...)    printf(x, ##args)
#else
    #define LOG_WRITE_FUNCTION(x, args...)    log_write(x, ##args)
#endif  /* SIMULATOR */


/** Enables basic log output on UART1 */
#define LOGGING

/** This is an example for a new stage of loging */
#define NEW_STAGE_LOGGING



#ifdef LOGGING
	#define LOG(x, args...)   LOG_WRITE_FUNCTION(x, ##args)
#else
	#define LOG(x, args...)
#endif /* LOGGING */


#ifdef NEW_STAGE_LOGGING
	#define NEW_STAGE_LOG(x, args...)   LOG_WRITE_FUNCTION(x, ##args)
#else
	#define NEW_STAGE_LOG(x, args...)
#endif /* NEW_STAGE_LOGGING */


void log_init(void);
void log_write(const char* format, ...);
void _format_number(int32_t number, int16_t base, int16_t digits, char padding, char* buffer);

#endif /* _LOG_H */



