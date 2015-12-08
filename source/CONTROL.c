/** 
 * @file        CONTROL.c
 *
 * @brief       CONTROL controls all input and output set and get function
 * 
 * @author      Florian Heidecker
 * @date        07.12.2015 - initial version
 *              08.12.2015 - PCM function implementation
 * 
 * @version     0.1
 */

#include "xc.h"

#include "log.h"
#include "global.h"
#include "CONTROL.h"
#include "PLL_API.h"
#include "PCM_API.h"
#include "SPI_API.h"

void CONTROL_init(void){
    CONTROL_LOG("CONTROL_LOG: spi_init()\n");
    spi_init();
    CONTROL_LOG("CONTROL_LOG: CONTROL_set_attunation_level = 100\n");
    CONTROL_set_attunation_level(100);
    CONTROL_LOG("CONTROL_LOG: CONTROL_set_zero_detect_mute = enabled\n");
    CONTROL_set_zero_detect_mute(PCM_enabled);
    CONTROL_LOG("CONTROL_LOG: CONTROL_set_monaural_mode = stereo\n");
    CONTROL_set_monaural_mode(PCM_stereo);
}

//== PLL/PCM/SRC related =======================================================


//== only PLL related ==========================================================


//== only PCM related ==========================================================

void CONTROL_set_attunation_level(uint8_t percent){
    // attenuation control must be set to 1
    PCM_set_attenuation_control(PCM_enabled);
    
    CONTROL_LOG("CONTROL_LOG: CONTROL_set_attunation_level,  input percent = %i\n", percent);
    // input value is proportional to attunation level
    uint8_t level = (uint8_t)(((uint16_t)((255 - 14) * percent ) / 100) + 14);
    CONTROL_LOG("CONTROL_LOG: CONTROL_set_attunation_level, output level = %i\n", level);
    
    PCM_set_attunation_level_left(level);
    PCM_set_attunation_level_right(level);
    
    // enable soft mute if level is below 14
    if(level <= 14){
        PCM_set_soft_mute(PCM_enabled);
    }
    else{
        PCM_set_soft_mute(PCM_disabled);
    }
}

uint8_t CONTROL_get_attunation_level(void){
    uint8_t level = PCM_get_attunation_level_left();
    CONTROL_LOG("CONTROL_LOG: CONTROL_get_attunation_level, input level = %i\n", level);
    
    // output value is proportional to attunation level
    uint8_t percent = (uint8_t)((uint16_t)(100 * (level - 14)) / (255 - 14));
    CONTROL_LOG("CONTROL_LOG: CONTROL_get_attunation_level,  output percent = %i\n", percent);
    return percent;
}

void CONTROL_set_soft_mute(uint8_t value){
    PCM_set_soft_mute(value);
}

uint8_t CONTROL_get_soft_mute(void){
    return PCM_get_soft_mute();
}

void CONTROL_set_zero_detect_mute(uint8_t value){
    PCM_set_zero_detect_mute(value);
}

uint8_t CONTROL_get_zero_detect_mute(void){
    return PCM_get_zero_detect_mute();
}

void CONTROL_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode){
    PCM_set_data_channel(PCM_left_channel);
    PCM_set_monaural_mode(PCM_monaural_mode);
}

PCM_monaural_mode_t CONTROL_get_monaural_mode(void){
    return PCM_get_monaural_mode();
}

CONTROL_zero_detection_t CONTROL_get_zero_detection(void){
    return (PCM_get_left_zero_detection() + (2 * PCM_get_rigth_zero_detection()));
}

//== only SRC related ==========================================================