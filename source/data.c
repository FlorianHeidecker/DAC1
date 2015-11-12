/*
 * File:   data.c
 * Author: Florian
 *
 * Created on 8. November 2015, 20:47
 */

#include "xc.h"
#include "data.h"

#define MAIN_MENU_LENGTH        4
#define SUB_MENU_LENGTH         5
#define PARAMETER_MENU_LENGTH   3


//==menu text array=============================================================
char* menu_text[MAIN_MENU_LENGTH][SUB_MENU_LENGTH][PARAMETER_MENU_LENGTH] = {
    { {"Titel_1", "\0", "\0"},{"Subtitel_11    ", "on", "off"},{"Subtitel_12", "\0", "\0"},{"Subtitel_13", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_2", "\0", "\0"},{"Subtitel_21    ", "414Hz", "96Hz"},{"Subtitel_22", "\0", "\0"},{"Subtitel_23", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_3", "\0", "\0"},{"Subtitel_31    ", "\0", "\0"},{"Subtitel_32", "\0", "\0"},{"Subtitel_33", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_4", "\0", "\0"},{"Subtitel_41    ", "\0", "\0"},{"Subtitel_42", "\0", "\0"},{"Subtitel_43", "\0", "\0"},{"return", "\0", "\0"} },
};

//==value array for settings====================================================
char* setting_value[MAIN_MENU_LENGTH][SUB_MENU_LENGTH][PARAMETER_MENU_LENGTH] = {
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
    { {1, 0, 0},{1, 0, 0},{1, 0, 0} },
};

//==save settings array index===================================================
char* setting_save[MAIN_MENU_LENGTH][SUB_MENU_LENGTH] = {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
};

// get main menu points
char* get_main_menu_max_index(){
    return (MAIN_MENU_LENGTH-1);
}

// get sub menu points
char* get_sub_menu_max_index(){
    return (SUB_MENU_LENGTH-1);
}

// get parameter menu points
char* get_parameter_menu_max_index(){
    return (PARAMETER_MENU_LENGTH-1);
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
