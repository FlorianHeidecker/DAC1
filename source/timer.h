/** 
 * @file        PLL_API.h
 *
 * @brief       timer and interrupt routine
 * 
 * @author      Florian Heidecker
 * @date        02.01.2016 - initial version
 * 
 * @version     0.1
 */

#ifndef _TIMER_H
#define _TIMER_H

#include <xc.h>

//== typedefs ==================================================================

/** interrupt states */
typedef enum {interrupt_no = 0, interrupt_yes = 1} interrrupt_state_t;

/** global variable, used to know the actual interrupt state*/
interrrupt_state_t interrrupt_state;

//== functions =================================================================

/**
 * @brief timer initialization
 */
void timer_init(void);

/**
 * @brief timer and interrupt started
 */
void timer_start(void);

/**
 * @brief timer and interrupt stopped
 */
void timer_stop(void);

#endif /* _TIMER_H */