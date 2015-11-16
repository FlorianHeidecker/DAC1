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
typedef enum {PLL_SCKO1_16MHz = 0, PLL_SCKO1_33MHz = 1} SCKO1_FREQ;

/** avalible sampling frequency in kHz */
typedef enum {PLL_SAMPLING_FREQ_48kHz=0,
              PLL_SAMPLING_FREQ_44_1kHz=1,
              PLL_SAMPLING_FREQ_32kHz=2,
              PLL_SAMPLING_FREQ_96kHz=4,
              PLL_SAMPLING_FREQ_88_2kHz=5,
              PLL_SAMPLING_FREQ_64kHz=6} SAMPLING_FREQ;

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



