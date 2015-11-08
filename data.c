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
    { {"Titel_1", "\0", "\0"},{"Subtitel_11    ", "on", "off"},{"Subtitel_12", "\0", "\0"},{"Subtitel_13", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_2", "\0", "\0"},{"Subtitel_21    ", "414Hz", "96Hz"},{"Subtitel_22", "\0", "\0"},{"Subtitel_23", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_3", "\0", "\0"},{"Subtitel_31    ", "\0", "\0"},{"Subtitel_32", "\0", "\0"},{"Subtitel_33", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_4", "\0", "\0"},{"Subtitel_41    ", "\0", "\0"},{"Subtitel_42", "\0", "\0"},{"Subtitel_43", "\0", "\0"},{"return", "\0", "\0"} },
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
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
};

// get main menu points
char* get_main_menu_length(){
    return main_menu_length;
}

// get sub menu points
char* get_sub_menu_length(){
    return sub_menu_length;
}

// get parameter menu points
char* get_parameter_menu_length(){
    return parameter_menu_length;
}

// get name menu text
char* get_name_text(char main_menu, char sub_menu){
    return menu_text[main_menu][sub_menu][0];
}

// get value menu text
char* get_value_text(char main_menu, char sub_menu){
    char parameter = setting_save[main_menu][sub_menu];
    return menu_text[main_menu][sub_menu][parameter];
}

// change setting it effects menu text and hardware setting
void set_setting(char main_menu, char sub_menu, char parameter_menu){
    setting_save[main_menu][sub_menu] = parameter_menu;
}

// get setting for hardware
char* get_setting(char main_menu, char sub_menu){
    char parameter = setting_save[main_menu][sub_menu];
    return setting_value[main_menu][sub_menu][parameter];
}
