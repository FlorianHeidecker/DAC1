/******************************************************************************
 ********************[ Renesas JCP2016 HL-3D Validation Test ]*****************	
 ******************************************************************************
 ** File:      	 log.c
 **----------------------------------------------------------------------------
 ** CREATED BY:  Sebastian Wolfarth 	    
 **----------------------------------------------------------------------------
 ** <version>		<Date>
 ** Comment
 **----------------------------------------------------------------------------
 ** v0.1		 Mon Aug 10 12:43:46 2015 
 ** Initial Version	
 **----------------------------------------------------------------------------
 ** (c)Continental Automotive GmbH		
 ******************************************************************************
 ** THIS FILE IS PROVIDED 'AS IS' WITHOUT WARRANTY OF ANY KIND. The IC-GROUP
 ** ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR ELIGIBILITY FOR
 ** ANY PURPOSES
 *****************************************************************************/


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
