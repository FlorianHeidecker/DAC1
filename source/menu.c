/**
 * @file    menu.c
 *
 * @brief   Main Function of DAC1 Project
 * 
 * This is the main routine of DAC1 Project.
 * 
 * @author  Sebastian Wolfarth
 * @date    29.10.15 - inital version
 * 
 * @version 0.1
 */

#include <stdio.h>
#include "menu.h"
#include "PLL_API.h"
#include "xlcd/xlcd.h"
#include "log.h"

const char ARROW[] = "*";

uint16_t menu_index = 0;
uint16_t menu_param_index = 0;
menu_state_t menu_state = 0;
//                                "01234567890123456789"
const char *info_main_menu_text[]     = {"Audio Informationen"};
const char *audio_main_menu_text[]    = {"Audio Einstellungen"};
const char *pll_main_menu_text[]      = {"PLL Einstellungen"};
const char *src_main_menu_text[]      = {"SRC Einstellungen"};
const char *pcm_main_menu_text[]      = {"PCM Einstellungen"};





const char *pll_sampling_freq_text[] =
{
    "Samp. Freq.", 
    "kHz",
    "48",
    "44.1",
    "32",
    "96",
    "88.2",
    "64"
};
const char *pll_scko_freq_text[] =
{
    "SCKO1 Freq.",
    "MHz",
    "16",
    "33"
};


const menu_t menu_arr[] =
{
    {info_main_menu_text,       0, PCM_MAIN_MENU,   AUDIO_MAIN_MENU,    0, 0, 0, 0},
    {audio_main_menu_text,      0, INFO_MAIN_MENU,  PLL_MAIN_MENU,      0, 0, 0, 0},
    {pll_main_menu_text,        0, AUDIO_MAIN_MENU, SRC_MAIN_MENU,      0, 0, 0, 0},
    {src_main_menu_text,        0, PCM_MAIN_MENU,   PLL_MAIN_MENU,      0, 0, 0, 0},
    {pll_sampling_freq_text,    6, 0,0,0,0, get_sampling_freq,  set_sampling_freq},
    {pll_scko_freq_text,        2, 0,0,0,0, get_scko1_freq,     set_scko1_freq}
};

void menu_init(void)
{
    menu_index = 0;
    menu_param_index = 0;
    menu_state = MAIN_MENU;
}


void menu_left(void)
{
    switch(menu_state)
    {
        case MAIN_MENU:
            break;
        case SUB_MENU:
            break;
        case PARAMETER_MENU:
            break;
        default:
            MENU_LOG("MENU: menu_left() ERR: menu_state=%i\n", menu_state);
            break;
    }
}

void menu_right(void)
{
    int menu_index_temp = 0;
    
    switch(menu_state)
    {
        case MAIN_MENU:
            menu_index_temp = menu_index;
            menu_index = menu_arr[menu_index].next;
            
            
            
            WriteCmdXLCD(XLCD_CLR_DISP);
            
            xlcd_goto(0,1);
            putrsXLCD(menu_arr[menu_index_temp].text[0]);
            
            xlcd_goto(1,0);
            putrsXLCD(ARROW);
            putrsXLCD(menu_arr[menu_index].text[0]);
            
            menu_index_temp = menu_arr[menu_index].next;
            xlcd_goto(2,1);
            putrsXLCD(menu_arr[menu_index_temp].text[0]);
            
            menu_index_temp = menu_arr[menu_index_temp].next;
            xlcd_goto(3,1);
            putrsXLCD(menu_arr[menu_index_temp].text[0]);                 
            break;
        case SUB_MENU:
            break;
        case PARAMETER_MENU:
            break;
        default:
            MENU_LOG("MENU: menu_left() ERR: menu_state=%i\n", menu_state);
            break;
    }
}

void menu_pressed(void)
{
    switch(menu_state)
    {
        case MAIN_MENU:
            break;
        case SUB_MENU:
            break;
        case PARAMETER_MENU:
            break;
        default:
            MENU_LOG("MENU: menu_left() ERR: menu_state=%i\n", menu_state);
            break;
    }
}

void menu_write_screen(void)
{
    
}


void menu_write_line(uint16_t line)
{
    //uint16_t menu_index = 0;
    //uint16_t param_index = 2;
    MENU_LOG("%s", menu_arr[menu_index].text[0]);  // write name
    
    xlcd_goto(line,0);
    putsXLCD((char*)menu_arr[menu_index].text[0]);
    
    // set cursor 14
    menu_param_index = menu_arr[menu_index].get();
    xlcd_goto(line, 13);
    putsXLCD((char*)menu_arr[menu_index].text[menu_param_index+2]);    // plus 2 to get right indice in array
    MENU_LOG(" %s", menu_arr[menu_index].text[menu_param_index+2]);
    
    // set cursor 18
    xlcd_goto(line, 17);
    putsXLCD((char*)menu_arr[menu_index].text[1]);
    MENU_LOG(" %s", menu_arr[menu_index].text[1]);
}


void menu_parameter_change(uint16_t rotation)
{
    switch(rotation)
    {
        case 1: // turn left
            menu_param_index--;
            
            if(menu_param_index >= menu_arr[menu_index].num_elements)
            {
                menu_param_index = menu_arr[menu_index].num_elements-1;
            }
            break;
            
        case 2: // button push
            menu_arr[menu_index].set(menu_param_index);
            menu_state = SUB_MENU;
            break;
            
        case 3: // turn right
            menu_param_index++;
            
            if(menu_param_index >= menu_arr[menu_index].num_elements)
            {
                menu_param_index = 0;
            }
            break;
            
        default:
            break;
            
    }
}


