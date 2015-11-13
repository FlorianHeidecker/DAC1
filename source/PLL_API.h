/** 
 * @file        PLL_API.h
 *
 * @brief       PLL_API contains the PLL basic functions
 *
 * This Module implements the PLL basis functionalities. The Module contains
 * functions to set the PLL output frequencys.
 * 
 * @author      Florian Heidecker
 * @date        13.11.2015 - initial version
 * 
 * @version     0.1
 *
 */

#ifndef _PLL_API_H
#define _PLL_API_H

#include <xc.h>

/** avalible frequenz output on SCKO1 in MHz */
typedef enum {_16 = 0, _33 = 1} SCKO1_FREQ;

/** avalible sampling frequency in kHz */
typedef enum {_48=0, _44_1=1, _32=2, _96=4, _88_2=5, _64=6} SAMPLING_FREQ;

/** PLL TRIS and LATCH initialization */
void pll_init();

/** set SCKO1 output frequency */
void set_SCKO1(SCKO1_FREQ);

/** set SCKO2 and SCKO3 output frequency */
void set_SCKO23(SAMPLING_FREQ);

/** get actuel SCKO1 output frequency */
SCKO1_FREQ get_SCKO1();

/** get actuel SCKO1 output frequency */
SAMPLING_FREQ get_SCKO23();

#endif /* _PLL_API_H */



