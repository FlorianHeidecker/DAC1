/** 
 * @file	log.c
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
 */


#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "log.h"


 void log_init(void)
 {
    SER_INIT();
 }

 void log_write(const char* str, ...)
 {
    char buffer[100];
    
    va_list params;
    va_start(params, str);
    vsprintf(buffer,str,params);
    va_end(params);

    SER_PUTS(buffer);
 }
