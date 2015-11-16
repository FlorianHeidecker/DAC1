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
    LOG("PLL init\n");
    PLL_CSEL_TRIS  = 0; /* output */
    PLL_SR_TRIS    = 0; /* output */
    PLL_FS1_TRIS   = 0; /* output */
    PLL_FS2_TRIS   = 0; /* output */
    
    set_SCKO1(PLL_SCKO1_33MHz);     /* default value */
    set_SCKO23(PLL_SAMPLING_FREQ_44_1kHz);  /* default value */
}

void set_SCKO1(SCKO1_FREQ scko1_freq){
    if(scko1_freq == PLL_SCKO1_16MHz) LOG("set SCKO1 FREQUENCY = PLL_SCKO1_16MHz\n");
    if(scko1_freq == PLL_SCKO1_33MHz) LOG("set SCKO1 FREQUENCY = PLL_SCKO1_33MHz\n");
    PLL_CSEL_LATCH = scko1_freq;
}

void set_SCKO23(SAMPLING_FREQ sampling_freq){
    switch(sampling_freq){
        case PLL_SAMPLING_FREQ_32kHz:
            LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_32kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case PLL_SAMPLING_FREQ_44_1kHz:
            LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_44_1kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_48kHz:
            LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_48kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_64kHz:
            LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_64kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case PLL_SAMPLING_FREQ_88_2kHz:
            LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_88_2kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_96kHz:
            LOG("set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_96kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 0;
            break;
    }
}

SCKO1_FREQ get_SCKO1(){
    return PLL_CSEL_LATCH;
}

SAMPLING_FREQ get_SCKO23(){
    SAMPLING_FREQ index = PLL_SR_LATCH*4 + PLL_FS2_LATCH*2 + PLL_FS1_LATCH;
    return index;
}

