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

#include <xc.h>
#include <stdint.h>
#include "global.h"

#ifndef _MENU_H
#define _MENU_H

typedef enum {
    MENU_NORMAL = 1,
    MENU_OPTION,
    MENU_OPTION_INT,
    MENU_WINDOW
}menu_type_t;

typedef enum {
    MENU_STATE_NORMAL = 1,
    MENU_STATE_PARAM_CHANGE
}menu_state_t;

typedef enum {
    MAIN_MENU_DUMMY = 0,
    AUDIO_INFO_MAIN_MENU,
    AUDIO_MAIN_MENU,
    EXPERT_MENU,      
    PLL_MAIN_MENU,
    SRC_MAIN_MENU,
    PCM_MAIN_MENU,
    EXPERT_RETURN_MENU,
    PLL_FREQ_SEL_MENU,
    PLL_SCKO_SEL_MENU,
    PLL_RETURN_MENU,
    PCM_MONAURAL_MENU,
    PCM_ATTUNATION_MENU,
    PCM_SOFT_MUTE_MENU,
    PCM_ZERO_DETECT_MUTE,
    PCM_AUDIO_DATA_FORMAT_MENU,
    PCM_DELTA_SIGMA_MENU,
    PCM_RETURN_MENU,
    CTRL_OVERSAMPLING_MENU,
    CTRL_AUDIO_FORMAT_MENU,
    CTRL_VOLUME_MENU,
    CTRL_SOFT_MUTE_MENU,
    CTRL_ZERO_MUTING_MENU,
    CTRL_MONAURAL_MENU,
    CTRL_RETURN_MENU,
    SRC_UPSAMPLING_MENU,
    SRC_MCLK_DIV_MENU,
    SRC_FORMAT_MENU,
    SRC_INTERPOLATION_MENU,
    SRC_MUTE_MENU,
    SRC_ERROR_MUTE_MENU,
    SRC_RETURN_MENU,
    AUDIO_INFO_SCREEN_MENU
            
            
            
}menu_index_t;

typedef struct menu_struct{
    const char **text;
    menu_type_t type;
    uint16_t num_elements;
    menu_index_t prev;
    menu_index_t next;
    menu_index_t up;
    menu_index_t sub;    
    uint16_t (*get)(void);
    void (*set)(uint16_t);
}menu_t;


// externe funktionen
void menu_init(void);
void menu_refresh(void);
void menu_btn_left(void);
void menu_btn_right(void);
void menu_btn_set(void);

#endif /* _MENU_H */
