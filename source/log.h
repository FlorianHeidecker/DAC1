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
#include "UART_API.h"

#ifndef _LOG_H
#define _LOG_H



/** Initialisation routine for the debug interface */
#define SER_INIT()		uart_init()
/** routine to send one char on the debug interface */
#define SER_PUTC(x)		uart_send_char(x)
/** routine to send a string on the debug interface */
#define SER_PUTS(x)		uart_send_string(x)


/** This define is set in MPLAB configuration for Simulator */
#ifdef SIMULATOR
    #define LOG_WRITE_FUNCTION(x, args...)    printf(x, ##args)
#else
    #define LOG_WRITE_FUNCTION(x, args...)    log_write(x, ##args)
#endif  /* SIMULATOR */


/** Enables basic log output on UART1 */
#define LOGGING
/** PLL API log output on UART1 */
#define PLL_API_LOGGING
/** Log function for PCM*/
#define PCM_API_LOGGING
/** Log function for XLCD library and menu */
#define XLCD_LOGGING
/** This is an example for a new stage of loging */
#define NEW_STAGE_LOGGING

#ifdef LOGGING
	#define LOG(x, args...)   LOG_WRITE_FUNCTION(x, ##args)
#else
	#define LOG(x, args...)
#endif /* LOGGING */


#ifdef PLL_API_LOGGING
	#define PLL_LOG(x, args...)   LOG_WRITE_FUNCTION(x, ##args)
#else
	#define PLL_LOG(x, args...)
#endif /* PLL_LOGGING */

#ifdef PCM_API_LOGGING
	#define PCM_LOG(x, args...)   LOG_WRITE_FUNCTION(x, ##args)
#else
	#define PCM_LOG(x, args...)
#endif /* PCM_LOGGING */

#ifdef XLCD_LOGGING
	#define XLCD_LOG(x, args...)   LOG_WRITE_FUNCTION(x, ##args)
#else
	#define XLCD_LOG(x, args...)
#endif /* NEW_STAGE_LOGGING */


#ifdef NEW_STAGE_LOGGING
	#define NEW_STAGE_LOG(x, args...)   LOG_WRITE_FUNCTION(x, ##args)
#else
	#define NEW_STAGE_LOG(x, args...)
#endif /* NEW_STAGE_LOGGING */


/** @brief Initializes logging function
 *
 * This functions calls all other functions which are needed to initialize
 * the logging module.
 */
void log_init(void);


/** @brief Formats and sends string
 *
 * Writes the C string pointed by format to output Interface using SER_PUTC() 
 * If format includes format specifiers (subsequences beginning with %), 
 * the additional arguments following format are formatted and inserted in the 
 * resulting string replacing their respective specifiers.
 *
 * @param format	String to send and add subsequences
 * @param ...		Arguments for the format specifiers
 */
void log_write(const char* format, ...);


/** @brief Helper Function to format the String
 *
 *  This functions formats an added subsequence similar to printf. 
 * 
 * @param number    Number to insert
 * @param base      Base of the number to insert (e.g. 10 for decimal system)
 * @param digits    Number of digits to add in the string
 * @param padding   Character to pad
 * @param buffer	Output buffer which will be filled 
 */
void _format_number(int32_t number, int16_t base, int16_t digits, char padding, char* buffer);

#endif /* _LOG_H */



