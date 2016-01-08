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
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "PLL_API.h"
#include "PCM_API.h"
#include "SRC_API.h"
#include "xlcd/xlcd.h"
#include "log.h"
#include "control.h"
#include "timer.h"

/** Maximum Number of Lines for the Menu */
#define MAX_LINE    (4-1)      

/** Cursor index for menu text */
#define TEXT_CURSOR_INDEX      0
/** start index of menu text */
#define TEXT_INDEX             1 
/** cursor index for menu option */
#define PARAM_CURSOR_INDEX     12
/** start index of menu option */
#define PARAM_INDEX            13
/** defines sign used for cursor */
#define CURSOR_SIGN ">"

/** control structur for whole menu module */
struct menu_control{
    /** index of current menu option */
    uint16_t index;
    /** index of menu parameter from current menu entry */
    uint16_t param_index;
    /** active cursor line */
    uint16_t cursor;
    /** state of current menu operation */
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
void menu_call_up(uint16_t dummy);
void menu_write_line(uint16_t line, uint16_t index);
void menu_refresh_lines(void);
void menu_write_headline(void);

//==============================================================================
// internal function declarations for special menu windows from MENU_WINDOW Type
//==============================================================================
void menu_show_audio_information(uint16_t btn_value);



//==============================================================================
// Definitions of Menu Text
//==============================================================================
//                                       "01234567890123456789"
const char *main_menu_text[]          = {"Main Menu"};
const char *info_main_menu_text[]     = {"Audio Info"};
const char *audio_main_menu_text[]    = {"Audio Settings"};
const char *expert_menu_text[]        = {"Expert Settings"};
const char *pll_main_menu_text[]      = {"PLL Settings"};
const char *src_main_menu_text[]      = {"SRC Settings"};
const char *pcm_main_menu_text[]      = {"PCM Settings"};
const char *return_menu_text[]        = {"RETURN ->"};
const char *control_volume_text[]     = {"Volume"};
const char *menu_dummy_text[]         = {"#DUMMY#"};


//==============================================================================
// Definitions of Menu Parameterlist
//==============================================================================
const char *pll_sampling_freq_text[] = {
    "SCKO2 Freq.", 
    "32kHz",
    "44.1kHz",
    "48kHz",
    "64kHz",
    "88.2kHz",
    "96kHz"
};
const char *pll_scko_freq_text[] = {
    "SCKO1 Freq.",
    "16MHz",
    "33MHz"
};

const char *pcm_attunation_text[] = {
    "Volume",
};
const char *pcm_soft_mute_text[] = {
    "SoftMute",
    "On",
    "Off"
};
const char *pcm_audio_data_format_text[] = {
    "Format",
    "16 LSB",
    "20 LSB",
    "24 LSB",
    "24 MSB",
    "16 I2S",
    "24 I2S"
};
const char *pcm_delta_sigma_text[] = {
    "DeltaSigma",
    "64fs",
    "32fs",
    "128fs"
};
const char *pcm_monaural_text[] = {
    "Monaural",
    "Stereo",
    "Mono"
};
const char *pcm_zero_detect_text[] = {
    "ZeroDetect",
    "Off",
    "On"
};


//==============================================================================
// Definitions of SRC Settings
//==============================================================================
const char *src_audio_output_format_text[] = {
    "Format",
    "24Bit L",
    "24 I2S",
    "16Bit R",
    "18Bit R",
    "20Bit R",
    "24Bit R"
};
const char *src_master_clock_divider_text[] = {
    "MCLK Div",
    "128",
    "256",
    "384",
    "512"
};
const char *src_port_a_source_text[] = {
    "Upsampling",
    "Off",
    "On"
};
const char *src_output_mute_text[] = {
    "Mute",  
    "Off",
    "On"
};
const char *src_mute_pll_error_text[] = {
    "Err. Mute",
    "Off",
    "On"
};
const char *src_interpolation_filter_text[] = {
    "Fil. Delay",
    "64 Samp",
    "32 Samp",
    "16 Samp",
    "8 Samp"
};



//==============================================================================
// Definitions of Audio Settings
//==============================================================================
const char *control_oversampling_text[] = {
    "Oversamp.",
    "32kHz",
    "44.1kHz",
    "48kHz",
    "64kHz",
    "88.2kHz",
    "96kHz",
    "192kHz"
};

const char *control_audio_format_text[] = {
    "Format",
    "16Bit R",
    "20Bit R",
    "24Bit R",
    "24Bit L",
    "24 I2S"
};

const char *control_soft_mute_text[] = {
    "Mute",
    "Off",
    "On"
};

const char *control_zero_detect_mute_text[] = {
    "Zero Muting",
    "Off",
    "On"
};

const char *control_monaural_text[] = {
    "Monaural",
    "Stereo",
    "Mono"
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
        .up  = AUDIO_INFO_MAIN_MENU,   // to get out of here
        .sub = AUDIO_INFO_MAIN_MENU,  // to get out of here
        .get = menu_get_nothing,
        .set = menu_call_sub
    },
    {   // AUDIO_INFO_MAIN_MENU
        .text = info_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev   = EXPERT_MENU,
        .next   = AUDIO_MAIN_MENU,
        .up     = MAIN_MENU_DUMMY,
        .sub    = AUDIO_INFO_SCREEN_MENU,
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // AUDIO_MAIN_MENU
        .text = audio_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = AUDIO_INFO_MAIN_MENU,  
        .next   = EXPERT_MENU,      
        .up     = MAIN_MENU_DUMMY, 
        .sub    = CTRL_OVERSAMPLING_MENU, 
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // EXPERT_MENU
        .text   = expert_menu_text,
        .type   = MENU_NORMAL,
        .num_elements = 0,
        .prev   = AUDIO_MAIN_MENU,
        .next   = AUDIO_INFO_MAIN_MENU,
        .up     = MAIN_MENU_DUMMY,
        .sub    = PLL_MAIN_MENU,
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // PLL_MAIN_MENU
        .text = pll_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0, 
        .prev   = EXPERT_RETURN_MENU, 
        .next   = SRC_MAIN_MENU,      
        .up     = EXPERT_MENU, 
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
        .up     = EXPERT_MENU, 
        .sub    = SRC_UPSAMPLING_MENU, 
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // PCM_MAIN_MENU
        .text = pcm_main_menu_text,
        .type = MENU_NORMAL,
        .num_elements = 0,
        .prev   = SRC_MAIN_MENU,
        .next   = EXPERT_RETURN_MENU,
        .up     = EXPERT_MENU,
        .sub    = PCM_MONAURAL_MENU,
        .get    = menu_get_nothing,
        .set    = menu_call_sub
    },
    {   // EXPERT_RETURN_MENU
        .text   = return_menu_text,      
        .type   = MENU_NORMAL,
        .num_elements = 0,
        .prev   = PCM_MAIN_MENU,
        .next   = PLL_MAIN_MENU,
        .up     = EXPERT_MENU,
        .sub    = 0,
        .get    = menu_get_nothing,
        .set    = menu_call_up
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
        .type   = MENU_OPTION_INT,
        .num_elements = 101,
        .prev   = PCM_MONAURAL_MENU,
        .next   = PCM_SOFT_MUTE_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = CONTROL_get_attunation_level,
        .set    = CONTROL_set_attunation_level,  
    },
    {   // PCM_SOFT_MUTE_MENU
        .text   = pcm_soft_mute_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = PCM_ATTUNATION_MENU,
        .next   = PCM_ZERO_DETECT_MUTE,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_soft_mute,
        .set    = PCM_set_soft_mute,  
    },
    {   // PCM_ZERO_DETECT_MUTE
        .text   = pcm_zero_detect_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = PCM_SOFT_MUTE_MENU,
        .next   = PCM_AUDIO_DATA_FORMAT_MENU,
        .up     = PCM_MAIN_MENU,
        .sub    = 0,
        .get    = PCM_get_zero_detect_mute,
        .set    = PCM_set_zero_detect_mute,
    },
    {   // PCM_AUDIO_DATA_FORMAT_MENU
        .text   = pcm_audio_data_format_text,
        .type   = MENU_OPTION,
        .num_elements = 6,
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
    },
    {   // CTRL_OVERSAMPLING_MENU
        .text   = control_oversampling_text,      
        .type   = MENU_OPTION,
        .num_elements = 7,
        .prev   = CTRL_RETURN_MENU,
        .next   = CTRL_AUDIO_FORMAT_MENU,
        .up     = AUDIO_MAIN_MENU,
        .sub    = 0,
        .get    = CONTROL_get_oversampling_freq,
        .set    = CONTROL_set_oversampling_freq
    },
    {   // CTRL_AUDIO_FORMAT_MENU
        .text   = control_audio_format_text,      
        .type   = MENU_OPTION,
        .num_elements = 5,
        .prev   = CTRL_OVERSAMPLING_MENU,
        .next   = CTRL_VOLUME_MENU,
        .up     = AUDIO_MAIN_MENU,
        .sub    = 0,
        .get    = CONTROL_get_audio_data_format,
        .set    = CONTROL_set_audio_data_format
    },
    {   // CTRL_VOLUME_MENU
        .text   = control_volume_text,      
        .type   = MENU_OPTION_INT,
        .num_elements = 101,
        .prev   = CTRL_AUDIO_FORMAT_MENU,
        .next   = CTRL_SOFT_MUTE_MENU,
        .up     = AUDIO_MAIN_MENU,
        .sub    = 0,
        .get    = CONTROL_get_attunation_level,
        .set    = CONTROL_set_attunation_level
    },
    {   // CTRL_SOFT_MUTE_MENU
        .text   = control_soft_mute_text,      
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = CTRL_VOLUME_MENU,
        .next   = CTRL_ZERO_MUTING_MENU,
        .up     = AUDIO_MAIN_MENU,
        .sub    = 0,
        .get    = CONTROL_get_soft_mute,
        .set    = CONTROL_set_soft_mute
    },
    {   // CTRL_ZERO_MUTING_MENU
        .text   = control_zero_detect_mute_text,      
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = CTRL_SOFT_MUTE_MENU,
        .next   = CTRL_MONAURAL_MENU,
        .up     = AUDIO_MAIN_MENU,
        .sub    = 0,
        .get    = CONTROL_get_zero_detect_mute,
        .set    = CONTROL_set_zero_detect_mute
    },
    {   // CTRL_MONAURAL_MENU
        .text   = control_monaural_text,      
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = CTRL_ZERO_MUTING_MENU,
        .next   = CTRL_RETURN_MENU,
        .up     = AUDIO_MAIN_MENU,
        .sub    = 0,
        .get    = CONTROL_get_monaural_mode,
        .set    = CONTROL_set_monaural_mode
    },
    {   // CTRL_RETURN_MENU
        .text   = return_menu_text,
        .type   = MENU_NORMAL,
        .num_elements = 0,
        .prev   = CTRL_MONAURAL_MENU,
        .next   = CTRL_OVERSAMPLING_MENU,
        .up     = AUDIO_MAIN_MENU,
        .sub    = 0,
        .get    = menu_get_nothing,
        .set    = menu_call_up
    },
    {   // SRC_UPSAMPLING_MENU
        .text   = src_port_a_source_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = SRC_RETURN_MENU,
        .next   = SRC_MCLK_DIV_MENU,
        .up     = SRC_MAIN_MENU,
        .sub    = 0,
        .get    = SRC_get_data_source,
        .set    = SRC_set_data_source
    },
    {   // SRC_MCLK_DIV_MENU
        .text   = src_master_clock_divider_text,
        .type   = MENU_OPTION,
        .num_elements = 4,
        .prev   = SRC_UPSAMPLING_MENU,
        .next   = SRC_FORMAT_MENU,
        .up     = SRC_MAIN_MENU,
        .sub    = 0,
        .get    = SRC_get_master_clock_divider,
        .set    = SRC_set_master_clock_divider
    },
    {   // SRC_FORMAT_MENU
        .text   = src_audio_output_format_text,
        .type   = MENU_OPTION,
        .num_elements = 6,
        .prev   = SRC_MCLK_DIV_MENU,
        .next   = SRC_INTERPOLATION_MENU,
        .up     = SRC_MAIN_MENU,
        .sub    = 0,
        .get    = SRC_get_audio_output_data_format,
        .set    = SRC_set_audio_output_data_format
    },
    {   // SRC_INTERPOLATION_MENU
        .text   = src_interpolation_filter_text,
        .type   = MENU_OPTION,
        .num_elements = 4,
        .prev   = SRC_FORMAT_MENU,
        .next   = SRC_MUTE_MENU,
        .up     = SRC_MAIN_MENU,
        .sub    = 0,
        .get    = SRC_get_interpolation_filter,
        .set    = SRC_set_interpolation_filter
    },
    {   // SRC_MUTE_MENU
        .text   = src_output_mute_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = SRC_INTERPOLATION_MENU,
        .next   = SRC_ERROR_MUTE_MENU,
        .up     = SRC_MAIN_MENU,
        .sub    = 0,
        .get    = SRC_get_output_mute,
        .set    = SRC_set_output_mute
    },
    {   // SRC_ERROR_MUTE_MENU
        .text   = src_mute_pll_error_text,
        .type   = MENU_OPTION,
        .num_elements = 2,
        .prev   = SRC_MUTE_MENU,
        .next   = SRC_RETURN_MENU,
        .up     = SRC_MAIN_MENU,
        .sub    = 0,
        .get    = SRC_get_mute_pll_error,
        .set    = SRC_set_mute_pll_error
    },
    {   // SRC_RETURN_MENU
        .text   = return_menu_text,
        .type   = MENU_NORMAL,
        .num_elements = 0,
        .prev   = SRC_ERROR_MUTE_MENU,
        .next   = SRC_UPSAMPLING_MENU,
        .up     = SRC_MAIN_MENU,
        .sub    = 0,
        .get    = menu_get_nothing,
        .set    = menu_call_up
    },
    {   // AUDIO_INFO_SCREEN_MENU
        .text   = menu_dummy_text,
        .type   = MENU_WINDOW,
        .num_elements = 0,
        .prev   = AUDIO_INFO_SCREEN_MENU,
        .next   = AUDIO_INFO_SCREEN_MENU,
        .up     = AUDIO_INFO_MAIN_MENU,
        .sub    = 0,
        .get    = menu_get_nothing,
        .set    = menu_show_audio_information 
    }
    
};

void menu_init(void)
{
    // set param
    m.index = AUDIO_INFO_SCREEN_MENU;
    m.param_index = 0;
    m.cursor = 1;
    m.state = MENU_NORMAL;
    
    //menu_btn_set();
    
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
        case MENU_WINDOW:
            // call set functions
            // this is menu_call_sub() for MENU_NORMAL
            menu_arr[m.index].set(1);
            break;
                        
        case MENU_OPTION:
        case MENU_OPTION_INT:
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


void menu_btn_right(void)
{
    switch(menu_arr[m.index].type)
    {
        case MENU_NORMAL:
            // loads next menu entries
            menu_call_next();     
            break;
            
        case MENU_OPTION:
        case MENU_OPTION_INT:
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
            
         case MENU_WINDOW:
            menu_arr[m.index].set(2);
            break;        
    }
}

void menu_refresh(void)
{
    switch(m.index)
    {
        case AUDIO_INFO_SCREEN_MENU:
            menu_show_audio_information(4);
            break;
            
        default:
            menu_write_headline();
            menu_refresh_lines();
            break;
    }
}

void menu_btn_left(void)
{    
    switch(menu_arr[m.index].type)
    {
        case MENU_NORMAL:
            // loads previous menu entries
            menu_call_prev();
            break;
            
        case MENU_OPTION:
        case MENU_OPTION_INT:
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
                        m.param_index = menu_arr[m.index].num_elements-1;
                    }
                    menu_write_line(m.cursor, m.index);
                    break;
            }
            break;
         case MENU_WINDOW:                     
            menu_arr[m.index].set(3);   
            break;    
    }
}


void menu_write_line(uint16_t line, uint16_t index)
{
    //uint16_t menu_index = 0;
    uint16_t param_index = 0;
    
    xlcd_clear_line(line);
    xlcd_goto(line, TEXT_INDEX);
    putrsXLCD(menu_arr[index].text[0]);
    //MENU_LOG("MENU: %s\n", menu_arr[index].text[0]); 
    
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
            if(param_index < menu_arr[index].num_elements)
            {
                putrsXLCD(menu_arr[index].text[param_index+1]);    // plus 2 to get right indice in array
                //MENU_LOG(" %s\n", menu_arr[index].text[param_index+1]);
            }
            else
            {
                MENU_LOG("MENU: param_index out of range: %i\n", param_index);
            }
            break;
        
        case MENU_OPTION_INT:
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
            if(param_index <= menu_arr[index].num_elements)
            {                
                char buf[10];
                ltoa(buf, param_index, 10);
                putsXLCD(buf);
                //putrsXLCD(menu_arr[index].text[param_index+1]);    // plus 1 to get right indice in array
                //MENU_LOG(" %s\n", buf);
            }
            else
            {
                MENU_LOG("MENU: param_index out of range: %i\n", param_index);
            }
            break;
            
        case MENU_WINDOW:   
            // nothing to do
            menu_arr[index].set(0);
            break;
    }
}


void menu_call_sub(uint16_t dummy)
{
    m.index = menu_arr[m.index].sub;
    m.cursor = 1;
    
    switch(menu_arr[m.index].type)
    {
        case MENU_NORMAL:
        case MENU_OPTION:
        case MENU_OPTION_INT:
            menu_write_headline();
            menu_refresh_lines();
            break;
            
        case MENU_WINDOW:
            menu_write_headline();
            menu_arr[m.index].set(0);
            break;
            
    }    
}


void menu_call_up(uint16_t dummy)
{
    m.index = menu_arr[m.index].up;
    m.cursor = 1;
    
    menu_write_headline();
    menu_refresh_lines();
    
    // this is only special feature for expert and non expert mode
    // this isnt the right place for implementing this but currently i have no 
    // better idea
    if(m.index == EXPERT_MENU)
    {
        // when leaving expert mode load default settings for audio
        CONTROL_init();
    }
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
        //xlcd_clear_line(1);
        menu_write_line(1, menu_arr[m.index].prev);
        //xlcd_clear_line(2);
        menu_write_line(2, m.index);
        //xlcd_clear_line(3);
        menu_write_line(3, menu_arr[m.index].next);  
    }
    
    //menu_write_headline();
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
        //xlcd_clear_line(1);
        menu_write_line(1, menu_arr[m.index].prev);
        //xlcd_clear_line(2);
        menu_write_line(2, m.index);
        //xlcd_clear_line(3);
        menu_write_line(3, menu_arr[m.index].next);
    }
    
    //menu_write_headline();
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
    menu_write_headline();
    menu_write_line(1, m.index);
    menu_write_line(2, menu_arr[m.index].next);
    menu_write_line(3, menu_arr[menu_arr[m.index].next].next); 
}

void menu_write_headline(void)
{
    uint16_t up_index = menu_arr[m.index].up;
    
    xlcd_clear_line(0);
    xlcd_goto(0,0);
    putrsXLCD("# ");
    putrsXLCD(menu_arr[up_index].text[0]);
    putrsXLCD(" #");
//    xlcd_goto(0,17);
//    ltoa(buf, m.cursor, 10);
//    putsXLCD(buf);
//    putrsXLCD("/");
//    ltoa(buf, menu_arr[up_index].num_elements, 10);
//    putsXLCD(buf);
    
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

void menu_show_audio_information(uint16_t btn_value)
{
    uint16_t temp;
    char buf[10];
    
    switch(btn_value)
    {
        case 0: // first call (write screen)
            timer_start();
        case 2: // btn down
        case 3: // btn up
            
            // 1. line
            menu_write_headline();
            
            // 2. line
            xlcd_clear_line(1);
            xlcd_goto(1,1);
            putrsXLCD("Track");

            // 3. line
            xlcd_clear_line(2);
            xlcd_goto(2,1);
            putrsXLCD("Playtime");
            
            // 4. line
            xlcd_clear_line(3);
            xlcd_goto(3,1);
            putrsXLCD("Oversamp.");
            
        case 4: // refresh from timer
            // 2. line option            
            temp = SRC_get_track();             
            ltoa(buf, temp, 10);
            xlcd_goto(1,PARAM_INDEX);
            putsXLCD(buf);
            putrsXLCD("   "); // clearing second character if switching from 2 digit to 1 digit
            
            // 3. line option
            temp = SRC_get_minutes();
            ltoa(buf, temp, 10);
            xlcd_goto(2, PARAM_INDEX);
            putsXLCD(buf);
            putrsXLCD(":");
            temp = SRC_get_seconds();
            _format_number(temp, 10, 2, '0', buf);
            //ltoa(buf, temp, 10);
            putsXLCD(buf);
            putrsXLCD("   "); // clearing second character if switching from 2 digit to 1 digit
            
            // 4. line option
            xlcd_goto(3, PARAM_INDEX);
            temp = CONTROL_get_oversampling_freq();
            
            if(temp < 7)
            {
                putrsXLCD(control_oversampling_text[temp+1]);
            }         
            break;
        
        case 1: // btn pressed
            timer_stop();
            menu_call_up(0);    // 0 is only a dummy
            break;
            
        default:
            MENU_LOG("MENU: menu_show_audio_information() btn_value out of range\n");
    }
}