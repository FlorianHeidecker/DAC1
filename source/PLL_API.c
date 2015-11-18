/** 
 * @file        PLL_API.c
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

#include <xc.h>

#include "log.h"
#include "global.h"
#include "PLL_API.h"

void pll_init(){
    PLL_LOG("PLL init\n");
    PLL_CSEL_TRIS  = 0; /* output */
    PLL_SR_TRIS    = 0; /* output */
    PLL_FS1_TRIS   = 0; /* output */
    PLL_FS2_TRIS   = 0; /* output */
    
    set_scko1_freq(PLL_SCKO1_33MHz);     /* default value */
    set_sampling_freq(PLL_SAMPLING_FREQ_44_1kHz);  /* default value */
}

void set_scko1_freq(scko1_freq_t scko1_freq){
    if(scko1_freq == PLL_SCKO1_16MHz) PLL_LOG("set SCKO1 FREQUENCY = PLL_SCKO1_16MHz\n");
    if(scko1_freq == PLL_SCKO1_33MHz) PLL_LOG("set SCKO1 FREQUENCY = PLL_SCKO1_33MHz\n");
    PLL_CSEL_LATCH = scko1_freq;
}

void set_sampling_freq(sampling_freq_t sampling_freq){
    switch(sampling_freq){
        case PLL_SAMPLING_FREQ_32kHz:
            PLL_LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_32kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case PLL_SAMPLING_FREQ_44_1kHz:
            PLL_LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_44_1kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_48kHz:
            PLL_LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_48kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_64kHz:
            PLL_LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_64kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case PLL_SAMPLING_FREQ_88_2kHz:
            PLL_LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_88_2kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_96kHz:
            PLL_LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_96kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 0;
            break;
    }
}

scko1_freq_t get_scko1_freq(){
    return PLL_CSEL_LATCH;
}

sampling_freq_t get_sampling_freq(){
    sampling_freq_t index = PLL_SR_LATCH*4 + PLL_FS2_LATCH*2 + PLL_FS1_LATCH;
    return index;
}

