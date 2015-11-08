/*
 * File:   data.c
 * Author: Florian
 *
 * Created on 8. November 2015, 20:47
 */

#include "xc.h"
#include "data.h"

const char main_menu_length = 3; // max array index
const char sub_menu_length = 4; // max array index
const char parameter_menu_length = 2; // max array index

//==menu text array=============================================================
char* menu_text [4][5][3]= {
    { {"Titel_1", "\0", "\0"},{"Subtitel_11", "on", "off"},{"Subtitel_12", "\0", "\0"},{"Subtitel_13", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_2", "\0", "\0"},{"Subtitel_21", "41", "96"},{"Subtitel_22", "\0", "\0"},{"Subtitel_23", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_3", "\0", "\0"},{"Subtitel_31", "\0", "\0"},{"Subtitel_32", "\0", "\0"},{"Subtitel_33", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_4", "\0", "\0"},{"Subtitel_41", "\0", "\0"},{"Subtitel_42", "\0", "\0"},{"Subtitel_43", "\0", "\0"},{"return", "\0", "\0"} },
};

//==value array for settings====================================================
char* setting_value [4][3][3]= {
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
};

//==save settings array index===================================================
char* setting_save [4][5] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};

char* get_main_menu_length(){
    return main_menu_length;
}

char* get_sub_menu_length(){
    return sub_menu_length;
}

char* get_parameter_menu_length(){
    return parameter_menu_length;
}

void set_setting(char main_menu, char sub_menu, char parameter_menu){
    setting_save[main_menu][sub_menu-1] = parameter_menu-1;
}

char* get_text(char main_menu, char sub_menu){
    return menu_text[main_menu][sub_menu][setting_save[main_menu][sub_menu-1]];
}

char* get_setting_value(char main_menu, char sub_menu){
    return setting_value[main_menu][sub_menu][setting_save[main_menu][sub_menu-1]];
}
