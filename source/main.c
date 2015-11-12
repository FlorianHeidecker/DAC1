/*
 * File:   main.c
 * Author: Sebastian
 *
 * Created on 29. Oktober 2015, 15:31
 */

#include <xc.h>
#include <stdio.h>

#include "menu.h"
#include "data.h"
#include "log.h"


int main(void) {
    LOG("main()\n");
    
    
    printf("\n==test data============================================\n");
    printf("%s%s\n",get_name_text(0,1), get_value_text(0,1));
    set_setting(0,1,2); // change setting to off
    printf("%s%s\n",get_name_text(0,1), get_value_text(0,1));
    printf("\n==test data============================================\n");
    
    
    while(1);
}