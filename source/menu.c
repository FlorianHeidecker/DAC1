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
#include "PCM_API.h"
#include "xlcd/xlcd.h"
#include "log.h"

/** Maximum Number of Lines for the Menu */
#define MAX_LINE    (4-1)      

#define TEXT_CURSOR_INDEX      0
#define TEXT_INDEX             1 
#define PARAM_CURSOR_INDEX     12
#define PARAM_INDEX            13
#define PARAM_UNIT_INDEX       17 


#define CURSOR_SIGN ">"

struct menu_control{
    uint16_t index;
    uint16_t param_index;
    uint16_t cursor;
    menu_state_t state;
}m;

//==============================================================================
// internal function declarations
//==============================================================================
void menu_set_nothing(uint16_t dummy);
uint16_t menu_get_nothing(void);
void menu_call_prev(void);
void menu_call_next(void);
void menu_call_sub(uint16_t dummy);
void menu_call_up(void);
void menu_write_line(uint16_t line, uint16_t index);
void menu_refresh_lines(void);
void menu_write_headline(void);



//==============================================================================
// Definitions of Menu Text
//==============================================================================
//                                       "01234567890123456789"
const char *main_menu_text[]          = {"Main Menu"};
const char *info_main_menu_text[]     = {"Audio Informationen"};
const char *audio_main_menu_text[]    = {"Audio Einstellungen"};
const char *pll_main_menu_text[]      = {"PLL Einstellungen"};
const char *src_main_menu_text[]      = {"SRC Einstellungen"};
const char *pcm_main_menu_text[]      = {"PCM Einstellungen"};
const char *return_menu_text[]        = {"RETURN ->"};


//==============================================================================
// Definitions of Menu Parameterlist
//==============================================================================
const char *pll_sampling_freq_text[] =
{
    "Samp. Freq.", 
    "  48kHz",
    "44.1kHz",
    "  32kHz",
    "  96kHz",
    "88.2kHz",
    "  64kHz"
};
const char *pll_scko_freq_text[] =
{
    "SCKO1 Freq.",
    "  16MHz",
    "  33MHz"
};

const char *pcm_attunation_text[] =
{
    "Attunation",
    "   xxdB",
    "   xxdB"
};

const char *pcm_soft_mute_text[] = 
{
    "SoftMute",
    "    On",
    "   Off"
};

const char *pcm_audio_data_format_text[] =
{
    "I2S Format",
    " 16 LSB",
    " 20 LSB",
    " 24 LSB",
    " 24 MSB",
    " 16 I2S",
    " 24 I2S"
};

const char *pcm_delta_sigma_text[] = 
{
    "DeltaSigma",
    "   64fs",
    "   32fs",
    "  128fs"
};

const char *pcm_monaural_text[] =
{
    "Monaural",
    "   Mono",
    " Stereo"
};

const char *pcm_zero_detect_text[] =
{
    "ZeroDetect"
    "     On",
    "    Off"
};

//==============================================================================
// Definitions Menu Structure
//==============================================================================
const menu_t menu_arr[] =
{
    {
        // MAIN_MENU
        .text = main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev = 0,
        .next = 0,
        .up = INFO_MAIN_MENU,   // to get out of here
        .sub = INFO_MAIN_MENU,  // to get out of here
        .get = menu_get_nothing,
        .set = menu_call_sub
    },
    {   // INFO_MAIN_MENU
        .text = info_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev   = PCM_MAIN_MENU,
        .next   = AUDIO_MAIN_MENU,
        .up     = MAIN_MENU_DUMMY,
        .sub    = 0,
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // AUDIO_MAIN_MENU
        .text = audio_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = INFO_MAIN_MENU,  
        .next   = PLL_MAIN_MENU,      
        .up     = MAIN_MENU_DUMMY, 
        .sub    = 0, 
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // PLL_MAIN_MENU
        .text = pll_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = AUDIO_MAIN_MENU, 
        .next   = SRC_MAIN_MENU,      
        .up     = MAIN_MENU_DUMMY, 
        .sub    = PLL_FREQ_SEL_MENU, 
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // SRC_MAIN_MENU
        .text = src_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = PLL_MAIN_MENU,   
        .next   = PCM_MAIN_MENU,      
        .up     = MAIN_MENU_DUMMY, 
        .sub    = 0, 
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // PCM_MAIN_MENU
        .text = pcm_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev   = SRC_MAIN_MENU,
        .next   = INFO_MAIN_MENU,
        .up     = MAIN_MENU_DUMMY,
        .sub    = PCM_MONAURAL_MENU,
        .get    = menu_get_nothing,
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
        .get  = PLL_get_sampling_freq,  
        .set  = PLL_set_sampling_freq
    },
    {   // PLL_SCKO_SEL_MENU
        .text = pll_scko_freq_text,     
        .type = MENU_OPTION,
        .num_elements = 2, 
        .prev = PLL_FREQ_SEL_MENU,
        .next = PLL_RETURN_MENU,
        .up   = PLL_MAIN_MENU,
        .sub  = 0, 
        .get  = PLL_get_scko1_freq,     
        .set  = PLL_set_scko1_freq
    },
    {   // PLL_RETURN_MENU
        .text   = return_menu_text,      
        .type   = MENU_NORMAL,
        .num_elements = 0,
        .prev   = PLL_SCKO_SEL_MENU,
        .next   = PLL_FREQ_SEL_MENU,
        .up     = PLL_MAIN_MENU,
        .sub    = 0,
        .get    = menu_get_nothing,
        .set    = menu_call_up
    },
    {   // PCM_MONAURAL_MENU
        .text   = pcm_monaural_text,      
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = PCM_RETURN_MENU,
        .next   = PCM_ATTUNATION_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_monaural_mode,
        .set    = PCM_set_monaural_mode,
    },
    {   // PCM_ATTUNATION_MENU
        .text   = pcm_attunation_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = PCM_MONAURAL_MENU,
        //.next   = PCM_SOFT_MUTE_MENU,
        .next   = PCM_ZERO_DETECT_MUTE,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_monaural_mode,
        .set    = PCM_set_monaural_mode,  
    },
    {   // PCM_SOFT_MUTE_MENU
        .text   = pcm_soft_mute_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = PCM_ATTUNATION_MENU,
        .next   = PCM_AUDIO_DATA_FORMAT_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_soft_mute,
        .set    = PCM_set_soft_mute,  
    },
    {   // PCM_ZERO_DETECT_MUTE
        .text   = pcm_zero_detect_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        //.prev   = PCM_SOFT_MUTE_MENU,
        .prev   = PCM_ATTUNATION_MENU,
        .next   = PCM_AUDIO_DATA_FORMAT_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_zero_detect_mute,
        .set    = PCM_set_zero_detect_mute,
    },
    {   // PCM_AUDIO_DATA_FORMAT_MENU
        .text   = pcm_audio_data_format_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = PCM_ZERO_DETECT_MUTE,
        .next   = PCM_DELTA_SIGMA_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_audio_data_format,
        .set    = PCM_set_audio_data_format,  
    },
    {   // PCM_DELTA_SIGMA_MENU
        .text   = pcm_delta_sigma_text,
        .type   = MENU_OPTION,
        .num_elements = 3,
        .prev   = PCM_AUDIO_DATA_FORMAT_MENU,
        .next   = PCM_RETURN_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_oversampling_rate,
        .set    = PCM_set_oversampling_rate,  
    },
        {   // PCM_RETURN_MENU
        .text   = return_menu_text,      
        .type   = MENU_NORMAL,
        .num_elements = 0,
        .prev   = PCM_DELTA_SIGMA_MENU,
        .next   = PCM_MONAURAL_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = menu_get_nothing,
        .set    = menu_call_up
    }
    
    
    
};

void menu_init(void)
{
    // set param
    m.index = INFO_MAIN_MENU;
    m.param_index = 0;
    m.cursor = 1;
    m.state = MENU_NORMAL;
    
    menu_write_headline();
    //menu_refresh_lines();
    
    
    xlcd_clear();
    //putrsXLCD("  ** MAIN MENU **");
    menu_write_headline();
    menu_write_line(1, m.index);
    menu_write_line(2, menu_arr[m.index].next);
    menu_write_line(3, menu_arr[menu_arr[m.index].next].next);   
}


void menu_btn_set(void)
{
    switch(menu_arr[m.index].type)
    {
        case MENU_NORMAL:
            // call set functions
            // this is menu_call_sub() for MENU_NORMAL
            menu_arr[m.index].set(0);
            break;
            
        case MENU_OPTION:
            switch(m.state)
            {
                case MENU_STATE_NORMAL:
                    // switch to Parameter change
                    m.state = MENU_STATE_PARAM_CHANGE;
                    
                    // change cursor to parameter
                    xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
                    putrsXLCD(" ");
                    xlcd_goto(m.cursor, PARAM_CURSOR_INDEX);
                    putrsXLCD(CURSOR_SIGN);
                    
                    // get index of current parameter
                    m.param_index = menu_arr[m.index].get();
                    break;
                    
                case MENU_STATE_PARAM_CHANGE:
                    // switch to normal menu operation
                    m.state = MENU_STATE_NORMAL;
                    
                    // change cursor to menu point
                    xlcd_goto(m.cursor, PARAM_CURSOR_INDEX);
                    putrsXLCD(" ");
                    xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
                    putrsXLCD(CURSOR_SIGN);
                    
                    // set selected parameter
                    menu_arr[m.index].set(m.param_index);
                    break;
            }
            break;
    }
}


void menu_btn_down(void)
{
    
    switch(menu_arr[m.index].type)
    {
        case MENU_NORMAL:
            // loads next menu entries
            menu_call_next();     
            break;
            
        case MENU_OPTION:
            switch(m.state)
            {
                case MENU_STATE_NORMAL:
                    // loads next menu entries
                    menu_call_next();
                    break;
                    
                case MENU_STATE_PARAM_CHANGE:
                    m.param_index++;
                    if(m.param_index >= menu_arr[m.index].num_elements)
                    {
                        m.param_index = 0;
                    }
                    menu_write_line(m.cursor, m.index);
                    break;
            }
            break;
    }
}

void menu_btn_up(void)
{    
    switch(menu_arr[m.index].type)
    {
        case MENU_NORMAL:
            // loads previous menu entries
            menu_call_prev();
            break;
            
        case MENU_OPTION:
            switch(m.state)
            {
                case MENU_STATE_NORMAL:
                    // loads next menu entries
                    menu_call_prev();
                    break;
                    
                case MENU_STATE_PARAM_CHANGE:
                    m.param_index--;
                    if(m.param_index >= menu_arr[m.index].num_elements)
                    {
                        m.param_index = menu_arr[m.index].num_elements - 1;
                    }
                    menu_write_line(m.cursor, m.index);
                    break;
            }
            break;
    }
}


void menu_write_line(uint16_t line, uint16_t index)
{
    //uint16_t menu_index = 0;
    uint16_t param_index;
    
    xlcd_clear_line(line);
    xlcd_goto(line, TEXT_INDEX);
    putrsXLCD(menu_arr[index].text[0]);
    MENU_LOG("MENU: %s", menu_arr[index].text[0]); 
    
    switch(menu_arr[index].type)
    {
        case MENU_NORMAL:
            // set cursor if write line = cursor line
            if(line == m.cursor)
            {
                xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
                putrsXLCD(CURSOR_SIGN);
            }
            break;
            
        case MENU_OPTION:
            switch(m.state)
            {
                case MENU_STATE_NORMAL:
                    param_index = menu_arr[index].get();
                    if(line == m.cursor)
                    {
                        xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
                        putrsXLCD(CURSOR_SIGN);
                    }
                    break;
  
                case MENU_STATE_PARAM_CHANGE:
                    param_index = m.param_index;
                    if(line == m.cursor)
                    {
                        xlcd_goto(m.cursor, PARAM_CURSOR_INDEX);
                        putrsXLCD(CURSOR_SIGN);
                    }
                    break;
            }
            
            // write parameter
            xlcd_goto(line, PARAM_INDEX);
            putrsXLCD(menu_arr[index].text[param_index+1]);    // plus 2 to get right indice in array
            MENU_LOG(" %s", menu_arr[index].text[param_index+1]);

//            // write unit
//            xlcd_goto(line, PARAM_UNIT_INDEX);
//            putrsXLCD(menu_arr[index].text[1]);
//            MENU_LOG(" %s", menu_arr[index].text[1]);
//            break;
    }
    
    MENU_LOG("\n");
}


void menu_call_sub(uint16_t dummy)
{
    m.index = menu_arr[m.index].sub;
    m.cursor = 1;
    
    menu_write_headline();
    menu_refresh_lines();
    
}


void menu_call_up(void)
{
    m.index = menu_arr[m.index].up;
    m.cursor = 1;
    
    menu_write_headline();
    menu_refresh_lines();
}


void menu_call_next(void)
{
    if(m.cursor < MAX_LINE)
    {
        // only move cursor
        xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
        putrsXLCD(" ");
        m.cursor++;
        xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
        putrsXLCD(CURSOR_SIGN);
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
        xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
        putrsXLCD(" ");
        m.cursor--;
        xlcd_goto(m.cursor, TEXT_CURSOR_INDEX);
        putrsXLCD(CURSOR_SIGN);
    }
    else
    {
        // cursor is already at line 1 
        // refresh screen
        xlcd_clear_line(1);
        menu_write_line(1, menu_arr[m.index].prev);
        xlcd_clear_line(2);
        menu_write_line(2, m.index);
        xlcd_clear_line(3);
        menu_write_line(3, menu_arr[m.index].next);
    }
    
    m.index = menu_arr[m.index].prev;
}


void menu_refresh_lines(void)
{
//    xlcd_clear_line(1);
//    menu_write_line(1, menu_arr[m.index].prev);
//    xlcd_clear_line(2);
//    menu_write_line(2, m.index);
//    xlcd_clear_line(3);
//    menu_write_line(3, menu_arr[m.index].next);   
    
    menu_write_line(1, m.index);
    menu_write_line(2, menu_arr[m.index].next);
    menu_write_line(3, menu_arr[menu_arr[m.index].next].next); 
}

void menu_write_headline(void)
{
    uint16_t up_index = menu_arr[m.index].up;
    
    xlcd_clear_line(0);
    xlcd_goto(0,0);
    putrsXLCD("*");
    putrsXLCD(menu_arr[up_index].text[0]);
    //putrsXLCD(" **");
}



void menu_set_nothing(uint16_t dummy)
{
    // empty function to do nothing
    // this function is used for "empty" functions pointers, to prevent 
    // programm from crashing
}

uint16_t menu_get_nothing(void)
{
    // empty function to do nothing
    // this function is used for "empty" functions pointers, to prevent 
    // programm from crashing
    return 0;
}



//void menu_parameter_change(uint16_t rotation)
//{
//    switch(rotation)
//    {
//        case 1: // turn left
//            m.param_index--;
//            
//            if(m.param_index >= menu_arr[m.index].num_elements)
//            {
//                m.param_index = menu_arr[m.index].num_elements-1;
//            }
//            break;
//            
//        case 2: // button push
//            menu_arr[m.index].set(m.param_index);
//            m.state = SUB_MENU;
//            break;
//            
//        case 3: // turn right
//            m.param_index++;
//            
//            if(m.param_index >= menu_arr[m.index].num_elements)
//            {
//                m.param_index = 0;
//            }
//            break;
//            
//        default:
//            break;
//            
//    }
//}
