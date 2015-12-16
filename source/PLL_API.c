/** 
 * @file        PLL_API.c
 *
 * @brief       PLL_API contains the PLL basic functions
 * 
 * @author      Florian Heidecker
 * @date        13.11.2015 - initial version
 *              07.12.2015 - rework/comments
 * 
 * @version     0.1
 */

#include <xc.h>

#include "log.h"
#include "global.h"
#include "PLL_API.h"

void PLL_init(void){
    PLL_CSEL_TRIS = 0;
    PLL_SR_TRIS = 0;
    PLL_FS1_TRIS = 0;
    PLL_FS2_TRIS = 0;
    
    PLL_set_scko1_freq(PLL_SCKO1_16MHz);
    PLL_set_sampling_freq(PLL_SAMPLING_FREQ_44_1kHz);
}

void PLL_set_scko1_freq(PLL_scko1_freq_t PLL_scko1_freq){
    if(PLL_scko1_freq == PLL_SCKO1_16MHz) PLL_LOG("PLL_LOG: set SCKO1 FREQUENCY = PLL_SCKO1_16MHz\n");
    if(PLL_scko1_freq == PLL_SCKO1_33MHz) PLL_LOG("PLL_LOG: set SCKO1 FREQUENCY = PLL_SCKO1_33MHz\n");
    PLL_CSEL_LATCH = PLL_scko1_freq;
}

PLL_scko1_freq_t PLL_get_scko1_freq(void){
    return PLL_CSEL_LATCH;
}

void PLL_set_sampling_freq(PLL_sampling_freq_t PLL_sampling_freq){
    switch(PLL_sampling_freq){
        case PLL_SAMPLING_FREQ_32kHz:
            PLL_LOG("PLL_LOG: set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_32kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case PLL_SAMPLING_FREQ_44_1kHz:
            PLL_LOG("PLL_LOG: set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_44_1kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_48kHz:
            PLL_LOG("PLL_LOG: set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_48kHz\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_64kHz:
            PLL_LOG("PLL_LOG: set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_64kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case PLL_SAMPLING_FREQ_88_2kHz:
            PLL_LOG("PLL_LOG: set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_88_2kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case PLL_SAMPLING_FREQ_96kHz:
            PLL_LOG("PLL_LOG: set SAMPLING FREQUENCY = PLL_SAMPLING_FREQ_96kHz\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 0;
            break;
    }
}

PLL_sampling_freq_t PLL_get_sampling_freq(void){
    PLL_sampling_freq_t index = PLL_SR_LATCH*4 + PLL_FS2_LATCH*2 + PLL_FS1_LATCH;
    return index;
}

