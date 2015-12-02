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
    MAIN_MENU = 1,
    SUB_MENU,
    PARAMETER_MENU    
}menu_state_t;

typedef enum {
    INFO_MAIN_MENU = 0,
    AUDIO_MAIN_MENU,
    PLL_MAIN_MENU,
    SRC_MAIN_MENU,
    PCM_MAIN_MENU
    
    
            
}menu_index_t;

typedef struct menu_struct{
    const char **text;
    uint16_t num_elements;
    uint16_t prev;
    uint16_t next;
    uint16_t up;
    uint16_t sub;    
    uint16_t (*get)(void);
    void (*set)(uint16_t);
}menu_t;




void menu_write_line(uint16_t line);


#endif /* _MENU_H */