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
    MENU_OPTION
}menu_type_t;

typedef enum {
    MENU_STATE_NORMAL = 1,
    MENU_STATE_PARAM_CHANGE
}menu_state_t;

typedef enum {
    INFO_MAIN_MENU = 0,
    AUDIO_MAIN_MENU,
    PLL_MAIN_MENU,
    SRC_MAIN_MENU,
    PCM_MAIN_MENU,
    PLL_FREQ_SEL_MENU,
    PLL_SCKO_SEL_MENU,
    PLL_RETURN_MENU,
          
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
void menu_btn_up(void);
void menu_btn_down(void);
void menu_btn_set(void);

// interne funktionen
void menu_write_line(uint16_t line, uint16_t index);


#endif /* _MENU_H */