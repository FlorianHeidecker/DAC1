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

//const char ARROW[] = "*";

#define MAX_LINE    (4-1)
#define ARROW ">"

struct menu_control{
    uint16_t index;
    uint16_t param_index;
    uint16_t cursor;
    menu_state_t state;
}m;

//==============================================================================
// Definitions of Menu Text
//==============================================================================
//                                       "01234567890123456789"
const char *info_main_menu_text[]     = {"Audio Informationen"};
const char *audio_main_menu_text[]    = {"Audio Einstellungen"};
const char *pll_main_menu_text[]      = {"PLL Einstellungen"};
const char *src_main_menu_text[]      = {"SRC Einstellungen"};
const char *pcm_main_menu_text[]      = {"PCM Einstellungen"};
const char *return_menu_text[]        = {"     >>RETURN<<"};


// internal function declarations
void menu_nothing(void);
void menu_call_sub(void);
void menu_call_up(void);



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
    {   // INFO_MAIN_MENU
        .text = info_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev   = PCM_MAIN_MENU,
        .next   = AUDIO_MAIN_MENU,
        .up     = 0,
        .sub    = 0,
        .get    = menu_nothing,
        .set    = menu_call_sub
    },
    {   // AUDIO_MAIN_MENU
        .text = audio_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = INFO_MAIN_MENU,  
        .next   = PLL_MAIN_MENU,      
        .up     = 0, 
        .sub    = 0, 
        .get    = menu_nothing,
        .set    = menu_call_sub
    },
    {   // PLL_MAIN_MENU
        .text = pll_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = AUDIO_MAIN_MENU, 
        .next   = SRC_MAIN_MENU,      
        .up     = 0, 
        .sub    = 0, 
        .get    = menu_nothing,
        .set    = menu_call_sub
    },
    {   // SRC_MAIN_MENU
        .text = src_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = PLL_MAIN_MENU,   
        .next   = PCM_MAIN_MENU,      
        .up     = 0, 
        .sub    = 0, 
        .get    = menu_nothing,
        .set    = menu_call_sub
    },
    {   // PCM_MAIN_MENU
        .text = pcm_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev   = SRC_MAIN_MENU,
        .next   = INFO_MAIN_MENU,
        .up     = 0,
        .sub    = 0,
        .get    = menu_nothing,
        .set    = menu_call_sub
    },
    {   // PLL_FREQ_SEL_MENU
        .text =  pll_sampling_freq_text,
        .type = MENU_OPTION,
        .num_elements = 6,
        .prev = PLL_RETURN_MENU,
        .next = PLL_SCKO_SEL_MENU,
        .up   = PLL_MAIN_MENU,
        .sub  = 0, 
        .get  = get_sampling_freq,  
        .set  = set_sampling_freq
    },
    {   // PLL_SCKO_SEL_MENU
        .text = pll_scko_freq_text,     
        .type = MENU_OPTION,
        .num_elements = 2, 
        .prev = PLL_FREQ_SEL_MENU,
        .next = PLL_RETURN_MENU,
        .up   = PLL_MAIN_MENU,
        .sub  = 0, 
        .get  = get_scko1_freq,     
        .set  = set_scko1_freq
    },
    {   // PLL_RETURN_MENU
        .text   = return_menu_text,      
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev   = PLL_SCKO_SEL_MENU,
        .next   = PLL_FREQ_SEL_MENU,
        .up     = PLL_MAIN_MENU,
        .sub    = 0,
        .get    = menu_nothing,
        .set    = menu_call_up
    }
};

void menu_init(void)
{
    // set param
    m.index = INFO_MAIN_MENU;
    m.param_index = 0;
    m.cursor = 1;
    m.state = MAIN_MENU;
    
    xlcd_clear();
    putrsXLCD("  ** MAIN MENU **");
    menu_write_line(1, m.index);
    menu_write_line(2, menu_arr[m.index].next);
    menu_write_line(3, menu_arr[menu_arr[m.index].next].next);   
}


void menu_btn_set(void)
{
    switch(menu_arr[m.index].type)
    {
        case MENU_NORMAL:
            break;
        case MENU_OPTION:
            break;
    }
}


void menu_down(void)
{
    switch(m.state)
    {
        case MAIN_MENU:
            break;
        case SUB_MENU:
            break;
        case PARAMETER_MENU:
            break;
        default:
            MENU_LOG("MENU: menu_left() ERR: m.state=%i\n", m.state);
            break;
    }
}

void menu_up(void)
{
    int menu_index_temp = 0;
    
    switch(m.state)
    {
        case MAIN_MENU:
            menu_index_temp = m.index;
            m.index = menu_arr[m.index].next;
             
            WriteCmdXLCD(XLCD_CLR_DISP);
            
            xlcd_goto(0,1);
            putrsXLCD(menu_arr[menu_index_temp].text[0]);
            
            xlcd_goto(1,0);
            putrsXLCD(ARROW);
            putrsXLCD(menu_arr[m.index].text[0]);
            
            menu_index_temp = menu_arr[m.index].next;
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
            MENU_LOG("MENU: menu_left() ERR: m.state=%i\n", m.state);
            break;
    }
}

void menu_set(void)
{
    switch(m.state)
    {
        case MAIN_MENU:
            break;
        case SUB_MENU:
            break;
        case PARAMETER_MENU:
            break;
        default:
            MENU_LOG("MENU: menu_left() ERR: m.state=%i\n", m.state);
            break;
    }
}


void menu_write_line(uint16_t line, uint16_t index)
{
    //uint16_t menu_index = 0;
    uint16_t param_index = 0;
    
    xlcd_clear_line(line);
    xlcd_goto(line,1);
    putrsXLCD(menu_arr[index].text[0]);
    MENU_LOG("MENU: %s", menu_arr[index].text[0]); 
    
    if(menu_arr[index].num_elements > 0)
    {
        // set cursor 14
        param_index = menu_arr[index].get();
        xlcd_goto(line, 13);
        putrsXLCD(menu_arr[index].text[param_index+2]);    // plus 2 to get right indice in array
        MENU_LOG(" %s", menu_arr[index].text[param_index+2]);

        // set cursor 18
        xlcd_goto(line, 17);
        putrsXLCD(menu_arr[index].text[1]);
        MENU_LOG(" %s", menu_arr[index].text[1]);
    }
    else
    {
        // not elements availabe, do nothing
    }
    MENU_LOG("\n");
}


void menu_parameter_change(uint16_t rotation)
{
    switch(rotation)
    {
        case 1: // turn left
            m.param_index--;
            
            if(m.param_index >= menu_arr[m.index].num_elements)
            {
                m.param_index = menu_arr[m.index].num_elements-1;
            }
            break;
            
        case 2: // button push
            menu_arr[m.index].set(m.param_index);
            m.state = SUB_MENU;
            break;
            
        case 3: // turn right
            m.param_index++;
            
            if(m.param_index >= menu_arr[m.index].num_elements)
            {
                m.param_index = 0;
            }
            break;
            
        default:
            break;
            
    }
}


void menu_nothing(void)
{
    // empty function to do nothing
}

void menu_call_sub(void)
{
    
}

void menu_call_up(void)
{

}

void menu_call_next(void)
{
    if(m.cursor < MAX_LINE)
    {
        // only move cursor
        xlcd_goto(m.cursor, 0);
        putrsXLCD(" ");
        m.cursor++;
        xlcd_goto(m.cursor, 0);
        putrsXLCD(ARROW);
    }
    else
    {
        // cursor is already at MAX_LINE
        // refresh screen
        xlcd_clear_line(1);
        menu_write_line(1, menu_arr[m.index].prev);
        xlcd_clear_line(2);
        menu_write_line(2, m.index);
        xlcd_clear_line(3);
        menu_write_line(3, menu_arr[m.index].next);  
    }
    
    m.index = menu_arr[m.index].next;
}


void menu_call_prev(void)
{
    if(m.cursor > 1)
    {
        // only move cursor
        xlcd_goto(m.cursor, 0);
        putrsXLCD(" ");
        m.cursor--;
        xlcd_goto(m.cursor, 0);
        putrsXLCD(ARROW);
    }
    else
    {
        // cursor is already at line 1 
        // refres screen
        xlcd_clear_line(1);
        menu_write_line(1, menu_arr[m.index].prev);
        xlcd_clear_line(2);
        menu_write_line(2, m.index);
        xlcd_clear_line(3);
        menu_write_line(3, menu_arr[m.index].next);
    }
    
    m.index = menu_arr[m.index].prev;
}
