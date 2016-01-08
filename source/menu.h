/**
 * @file    menu.h
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


/** different types of menu points / entries */
typedef enum {
    MENU_NORMAL = 1,
    MENU_OPTION,
    MENU_OPTION_INT,
    MENU_WINDOW
}menu_type_t;

/** Menu states used for different menu options */
typedef enum {
    MENU_STATE_NORMAL = 1,
    MENU_STATE_PARAM_CHANGE
}menu_state_t;


/** used to initialize menu_arr with names */
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
    SRC_INTERPOLATION_FILTER_MENU,        
    SRC_INTERPOLATION_DELAY_MENU,
    SRC_MUTE_MENU,
    SRC_ERROR_MUTE_MENU,
    SRC_RETURN_MENU,
    AUDIO_INFO_SCREEN_MENU         
                
}menu_index_t;

/** Default Structure for one menu entry */
typedef struct menu_struct{
    /** pointer to an array of strings (char arrays), the first entry is the text
      * the following the Optional menu optsions. Only used for menu_option */
    const char **text;
    /** defines the menu type for this entry */
    menu_type_t type;
    /** defines number of elements for menu_option type */
    uint16_t num_elements;
    /** index of previous menu entry */
    menu_index_t prev;
    /** index of next menu entry */
    menu_index_t next;
    /** index of menu above the current menu entry */
    menu_index_t up;
    /** index of submenu from current menu, set to zero if no submenu available */
    menu_index_t sub;  
    /** function pointer to get current value for menu_option 
      * return value [0...num_elements-1]; only for MENU_OPTION */
    uint16_t (*get)(void);
    /** function pointer to set selected value for menu option
      * set value [0..num_elements-1]; in menu_option
      * for other menu types e.g. menu_call_sub() is used */
    void (*set)(uint16_t);
}menu_t;


/** @brief Initalizes Menu 
 * 
 * This Function initalizes menu structure for operation an prints 
 * default screen on the xlcd.
 */
void menu_init(void);

/** @brief Refreshes menu 
 * 
 * Refreshes all lines currently displayed by the menu. Including headline.
 */
void menu_refresh(void);

/** @brief Menu operation for button turn left
 * 
 * This executes menu operation for button left or rotary left.
 * The exact operation is determined by the menu_type and the current status of 
 * the menu. 
 * 
 * @note Call this functions after the button event
 */
void menu_btn_left(void);

/** @brief Menu operation for button turn right
 * 
 * This executes menu operation for button right or rotary right.
 * The exact operation is determined by the menu_type and the current status of 
 * the menu. 
 * 
 * @note Call this functions after the button event
 */
void menu_btn_right(void);

/** @brief Menu operation for button pressed
 * 
 * This executes menu operation for button pressed
 * The exact operation is determined by the menu_type and the current status of 
 * the menu. 
 * 
 * @note Call this functions after the button event
 */
void menu_btn_set(void);

#endif /* _MENU_H */
