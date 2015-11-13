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
    
    set_SCKO1(_33);     /* default value */
    set_SCKO23(_44_1);  /* default value */
}

void set_SCKO1(SCKO1_FREQ scko1_freq){
    if(scko1_freq == _16) LOG("set SCKO1 FREQUENCY = _16\n");
    if(scko1_freq == _33) LOG("set SCKO1 FREQUENCY = _33\n");
    PLL_CSEL_LATCH = scko1_freq;
}

void set_SCKO23(SAMPLING_FREQ sampling_freq){
    switch(sampling_freq){
        case _32:
            LOG("set SAMPLING FREQUENCY = _32\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case _44_1:
            LOG("set SAMPLING FREQUENCY = _44_1\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case _48:
            LOG("set SAMPLING FREQUENCY = _48\n");
            PLL_SR_LATCH  = 0;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 0;
            break;
        case _64:
            LOG("set SAMPLING FREQUENCY = _64\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 0;
            PLL_FS2_LATCH = 1;
            break;
        case _88_2:
            LOG("set SAMPLING FREQUENCY = _88_2\n");
            PLL_SR_LATCH  = 1;
            PLL_FS1_LATCH = 1;
            PLL_FS2_LATCH = 0;
            break;
        case _96:
            LOG("set SAMPLING FREQUENCY = _96\n");
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

