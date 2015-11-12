/*
 * File:   menu.h
 * Author: Florian Heidecker
 *
 * Created on 8. November 2015, 11:20
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_data_H
#define	XC_data_H

#include <xc.h>

// get main/sub/parameter menu points
char* get_main_menu_length();
char* get_sub_menu_length();
char* get_parameter_menu_length();

// get name/value menu text
char* get_name_text(char main_menu, char sub_menu);
char* get_value_text(char main_menu, char sub_menu);

// change setting it effects menu text and hardware setting
void set_setting(char main_menu, char sub_menu, char parameter_menu);

// get setting for hardware
char* get_setting(char main_menu, char sub_menu);

#endif