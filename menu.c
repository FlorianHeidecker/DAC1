/*
 * File:   menu.c
 * Author: Florian Heidecker
 *
 * Created on 8. November 2015, 11:20
 */

#include "xc.h"
#include <stdio.h>

#include "menu.h"

//==menu text array=============================================================
const char max_main_menu = 3; // max array index
const char max_sub_menu = 4; // max array index
const char max_parameter_menu = 2; // max array index
char* menu_view [4][5][3]= {
    { {"Titel_1", "\0", "\0"},{"Subtitel_11", "on", "off"},{"Subtitel_12", "\0", "\0"},{"Subtitel_13", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_2", "\0", "\0"},{"Subtitel_21", "41", "96"},{"Subtitel_22", "\0", "\0"},{"Subtitel_23", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_3", "\0", "\0"},{"Subtitel_31", "\0", "\0"},{"Subtitel_32", "\0", "\0"},{"Subtitel_33", "\0", "\0"},{"return", "\0", "\0"} },
    { {"Titel_4", "\0", "\0"},{"Subtitel_41", "\0", "\0"},{"Subtitel_42", "\0", "\0"},{"Subtitel_43", "\0", "\0"},{"return", "\0", "\0"} },
};

//==menu level stats============================================================
const char MAIN_MENU = 0; // top menu level eg.: properties
const char SUB_MENU = 1;       // bottom menu level eg.: mute
const char PARAMETER_MENU = 2; // parameter level eg.: on/off

char menu_level; // actual menu level

//==actual menu state/ index====================================================
char main_menu;      // actual index for array
char sub_menu;       // actual index for array
char parameter_menu; // actual index for array

//==rotary encoder state========================================================
const char NONE = 0;       // rotary encoder, nothing happents
const char TURN_LEFT = 1;  // rotary encoder, turn left
const char TURN_RIGHT = 2; // rotary encoder, turn right
const char ENTER = 3;      // rotary encoder, enter

//==menu setup/ start values====================================================
void menu_setup() {
    menu_level = MAIN_MENU; // start at top level
    char main_menu = 0;
    char sub_menu = 0;
    char parameter_menu = 0;
    
    //printf(menu_view[2][0][0]);
    //printf("  ");
    //printf(menu_view[2][0][1]);
}

void menu_loop(char rotary_encoder){
    switch(menu_level){         // state machine of menu level
        case 0: //(=MAIN_MENU)  // turn left/right and select sub menu  
            sub_menu = 0;       // prevent cross-effects
            parameter_menu = 0; // prevent cross-effects
            
            if(rotary_encoder = TURN_LEFT){
                main_menu--;
                if(main_menu == 0){
                    main_menu = max_main_menu;
                }
            }
            
            if(rotary_encoder = TURN_RIGHT){
                main_menu++;
                if(main_menu == max_main_menu){
                    main_menu = 0;
                }
            }
            
            if(rotary_encoder = ENTER){
                menu_level = SUB_MENU;
            }
            
            break;            // end MAIN_MENU
        case 1://(=SUB_MENU) // turn left/right and select parameter menu  
            
            if(rotary_encoder = TURN_LEFT){
                sub_menu--;
                if(sub_menu == 0){
                    sub_menu = max_sub_menu;
                }
            }
            
            if(rotary_encoder = TURN_RIGHT){
                sub_menu++;
                if(sub_menu == max_sub_menu){
                    sub_menu = 0;
                }
            }
            
            if(rotary_encoder = ENTER){
                if(sub_menu != max_sub_menu){
                    menu_level = PARAMETER_MENU;
                }
                else{
                    menu_level = MAIN_MENU;
                }
            }
            
            break;                  // end SUB_MENU
        case 2: //(=PARAMETER_MENU) // turn left/right and change(enter) parameter value
            
            if(rotary_encoder = TURN_LEFT){
                parameter_menu--;
                if(parameter_menu == 0){
                    parameter_menu = max_parameter_menu;
                }
            }
            
            if(rotary_encoder = TURN_RIGHT){
                parameter_menu++;
                if(parameter_menu == max_parameter_menu){
                    parameter_menu = 0;
                }
            }
            
            if(rotary_encoder = ENTER){
                menu_level = SUB_MENU;
            }
            
            break; // end PARAMETER_MENU
    };
}
