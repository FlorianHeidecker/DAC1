/*
 * File:   menu.h
 * Author: Florian Heidecker
 *
 * Created on 8. November 2015, 11:20
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_MENU_H
#define	XC_MENU_H

#include <xc.h>

void menu_setup();
void menu_loop(char rotary_encoder);

#endif

