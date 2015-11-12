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

#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

#include "log.h"

#define LTOA_BUFSIZE    12


 

char *ltoa(long N, char *str, int base)
{
      register int i = 2;
      long uarg;
      char *tail, *head = str, buf[LTOA_BUFSIZE];

      if (36 < base || 2 > base)
            base = 10;                    /* can only use 0-9, A-Z        */
      tail = &buf[LTOA_BUFSIZE - 1];           /* last character position      */
      *tail-- = '\0';

      if (10 == base && N < 0L)
      {
            *head++ = '-';
            uarg    = -N;
      }
      else  uarg = N;

      if (uarg)
      {
            for (i = 1; uarg; ++i)
            {
                  register ldiv_t r;

                  r       = ldiv(uarg, base);
                  *tail-- = (char)(r.rem + ((9L < r.rem) ?
                                  ('A' - 10L) : '0'));
                  uarg    = r.quot;
            }
      }
      else  *tail-- = '0';

      memcpy(head, ++tail, i);
      return str;
}
 


 void log_init(void)
 {
    SER_INIT();
 }
 
 
 void log_write(const char* format, ...)
 {
 	 va_list params;
	 va_start (params, format);	

    char temp;
    char *pchar;
    char buffer[17];

    char digits  = 0;
    char padding = ' ';

    char byte = *format++;
    while (byte != 0)
    {
       if (byte != '%') 
       {
          SER_PUTC(byte);
       }
       else
       {
			/* Get next byte from format string 
			  */
			  byte = *format++;
			  if (byte == 0) break;
          
			  if (isdigit(byte))
			  {
				/* convert to number and remember it
				 */
				 digits = byte - '0';

				 if (digits == 0)
				 {
					padding = '0';

				   /* Get next byte from format string 
					*/
					byte = *format++;
					if (byte == 0) break;

					if (isdigit(byte))
					{
					   digits = byte - '0';
					}
				 }

				/* Get next byte from format string 
				 */
				 byte = *format++;
				 if (byte == 0) break;
			  }

			switch (byte)
			{
				case 'c':   temp = va_arg(params, int16_t);
							SER_PUTC(temp);
							break;
             
				case 's':   pchar = va_arg(params, char*);
							SER_PUTS(pchar);
							break;

				case 'i':   _format_number(va_arg(params, int16_t), 10, digits, padding, buffer);
							SER_PUTS(buffer);
							break;

				case 'x':   _format_number(va_arg(params, int16_t), 16, digits, padding, buffer);
							SER_PUTS(buffer);
							break;
             
				case 'b':   _format_number(va_arg(params, int16_t), 2, digits, padding, buffer);
							SER_PUTS(buffer);
							break;
			}
       }
      
		/* Get next byte from format string 
       */
       byte = *format++;

    };
	va_end(params);
 }


 void _format_number(int32_t number, int16_t base, int16_t digits, char padding, char* buffer)
 {
    char temp[33];
    int16_t  pad = 0;
    int16_t  len = 0;
    int16_t index = 0;    
    
    memset(temp, 0, 17);

    if (buffer != NULL)
    {
       ltoa(number, temp, base);
       len = strlen(temp);
      
       if (digits > 0)
       {
          pad = digits - len;
       }

       if (temp[0] == '-')
       {
          buffer[0] = '-';
          ++index;
       }
       
       while (pad > 0)
       {
          buffer[index] = padding;
          ++index;
          --pad;
       }
       strcpy(buffer + index, temp);
    }
 }
 
 
 /*
 void log_write(const char* str, ...)
 {
    char buffer[100];
    
    va_list params;
    va_start(params, str);
    vsprintf(buffer,str,params);
    va_end(params);

    SER_PUTS(buffer);
 }
*/