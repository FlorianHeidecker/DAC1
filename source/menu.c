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
#include "xlcd.h"

static uint16_t menu_index = 0;
static uint16_t menu_param_index = 0;
static menu_state_t menu_state = 0;


const char *pll_sampling_freq_text[] =
{
    "Samp. Frequency", 
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
    "SCKO1 Frequency",
    "MHz",
    "16",
    "33"
};


const menu_t menu_arr[] =
{
    {pll_sampling_freq_text,    6, 0,0,0,0, get_sampling_freq,  set_sampling_freq},
    {pll_scko_freq_text,        2, 0,0,0,0, get_scko1_freq,     set_scko1_freq}
};

void menu_init(void)
{
    menu_index = 0;
    menu_param_index = 0;
    menu_state = MAIN_MENU;
}




void menu_write_line(uint16_t line)
{
    //uint16_t menu_index = 0;
    //uint16_t param_index = 2;
    printf("%s", menu_arr[menu_index].text[0]);  // write name
    
    // set cursor 14
    menu_param_index = menu_arr[menu_index].get();
    
    // plus 2 to get right indice in array
    printf(" %s", menu_arr[menu_index].text[menu_param_index+2]);
    
    // set cursor 18
    
    printf(" %s", menu_arr[menu_index].text[1]);
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


