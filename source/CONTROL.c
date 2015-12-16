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

#define bottom_border_level 135

typedef enum {	CONTROL_16_bit_standard_format=0,
				CONTROL_20_bit_standard_format=1,
				CONTROL_24_bit_standard_format=2,
				CONTROL_24_bit_MSB_first=3,
				CONTROL_24_bit_I2S=4} CONTROL_audio_data_format_t;

void CONTROL_init(void){
    CONTROL_LOG("CONTROL_LOG: spi_init()\n");
    spi_init();
    PLL_init();
    SRC_init();
    PLL_set_scko1_freq(PLL_SCKO1_16MHz);
    CONTROL_set_audio_data_format(CONTROL_24_bit_I2S);
    CONTROL_set_attunation_level(100);
    CONTROL_set_zero_detect_mute(PCM_enabled);
    CONTROL_set_monaural_mode(PCM_stereo);
}

//== PLL/PCM/SRC related =======================================================
void CONTROL_set_audio_data_format(CONTROL_audio_data_format_t CONTROL_audio_data_format){
    switch(CONTROL_audio_data_format){
        case CONTROL_16_bit_standard_format:
            PCM_set_audio_data_format(PCM_16_bit_standard_format);
            SRC_set_audio_output_data_format(SRC_16_bit_right_justified);
            SRC_set_word_length(SRC_WORD_LENGTH16);
            break;
            
        case CONTROL_20_bit_standard_format:
            PCM_set_audio_data_format(PCM_20_bit_standard_format);
            SRC_set_audio_output_data_format(SRC_20_bit_right_justified);
            SRC_set_word_length(SRC_WORD_LENGTH20);
            break;
            
        case CONTROL_24_bit_standard_format:
            PCM_set_audio_data_format(PCM_24_bit_standard_format);
            SRC_set_audio_output_data_format(SRC_24_bit_right_justified);
            SRC_set_word_length(SRC_WORD_LENGTH24);
            break;
            
        case CONTROL_24_bit_MSB_first:
            PCM_set_audio_data_format(PCM_24_bit_MSB_first);
            SRC_set_audio_output_data_format(SRC_24_bit_left_justified);
            SRC_set_word_length(SRC_WORD_LENGTH24);
            break;
            
        case CONTROL_24_bit_I2S:
            PCM_set_audio_data_format(PCM_24_bit_I2S);
            SRC_set_audio_output_data_format(SRC_24_bit_I2S);
            SRC_set_word_length(SRC_WORD_LENGTH24);
            break;
    }
}

CONTROL_audio_data_format_t CONTROL_get_audio_data_format(void){
    switch(PCM_get_audio_data_format()){
        case PCM_16_bit_standard_format:
            return CONTROL_16_bit_standard_format;
            break;
            
        case PCM_20_bit_standard_format:
            return CONTROL_20_bit_standard_format;
            break;
            
        case PCM_24_bit_standard_format:
            return CONTROL_24_bit_standard_format;
            break;
            
        case PCM_24_bit_MSB_first:
            return CONTROL_24_bit_MSB_first;
            break;
            
        case PCM_24_bit_I2S:
            return CONTROL_24_bit_I2S;
            break;
    }
}

void CONTROL_reset(void){
    PCM_pcm_reset(PCM_enabled);
    SRC_set_reset(1);
    CONTROL_init();
}

//== only PLL related ==========================================================


//== only PCM related ==========================================================

void CONTROL_set_attunation_level(uint8_t percent){
    // attenuation control must be set to 1
    CONTROL_LOG("CONTROL_LOG: PCM_set_attenuation_control = enabled\n");
    PCM_set_attenuation_control(PCM_enabled);
    
    CONTROL_LOG("CONTROL_LOG: CONTROL_set_attunation_level, input percent = %i\n", percent);
    // input value is proportional to attunation level
    uint8_t level = (uint8_t)(((uint16_t)((255 - bottom_border_level) * percent ) / 100) + bottom_border_level);
    CONTROL_LOG("CONTROL_LOG: CONTROL_set_attunation_level, output level = %i\n", level);
    
    PCM_set_attenuation_level_left(level);
    PCM_set_attenuation_level_right(level);
    
    // enable soft mute if level is below 14
    if(level <= 14){
        PCM_set_soft_mute(PCM_enabled);
    }
    else{
        PCM_set_soft_mute(PCM_disabled);
    }
}

uint8_t CONTROL_get_attunation_level(void){
    uint8_t level = PCM_get_attenuation_level_left();
    CONTROL_LOG("CONTROL_LOG: CONTROL_get_attunation_level, input level = %i\n", level);
    
    // output value is proportional to attunation level
    uint8_t percent = (uint8_t)((uint16_t)(100 * (level - bottom_border_level)) / (255 - bottom_border_level));
    CONTROL_LOG("CONTROL_LOG: CONTROL_get_attunation_level, output percent = %i\n", percent);
    return percent;
}

void CONTROL_set_soft_mute(uint8_t value){
    if(value == PCM_enabled){
        CONTROL_LOG("CONTROL_LOG: PCM_set_soft_mute = enabled");
    }
    else{
        CONTROL_LOG("CONTROL_LOG: PCM_set_soft_mute = disabled");
    }
    PCM_set_soft_mute(value);
}

uint8_t CONTROL_get_soft_mute(void){
    return PCM_get_soft_mute();
}

void CONTROL_set_zero_detect_mute(uint8_t value){
    if(value == PCM_enabled){
        CONTROL_LOG("CONTROL_LOG: PCM_set_zero_detect_mute = enabled");
    }
    else{
        CONTROL_LOG("CONTROL_LOG: PCM_set_zero_detect_mute = disabled");
    }
    PCM_set_zero_detect_mute(value);
}

uint8_t CONTROL_get_zero_detect_mute(void){
    return PCM_get_zero_detect_mute();
}

void CONTROL_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode){
    if(PCM_monaural_mode == PCM_stereo){
        CONTROL_LOG("CONTROL_LOG: PCM_set_monaural_mode = stereo");
        PCM_set_monaural_mode(PCM_monaural_mode);
    }
    else{
        CONTROL_LOG("CONTROL_LOG: PCM_set_data_channel = PCM_left_channel");
        PCM_set_data_channel(PCM_left_channel);
        CONTROL_LOG("CONTROL_LOG: PCM_set_monaural_mode = mono");
        PCM_set_monaural_mode(PCM_monaural_mode);
    }
}

PCM_monaural_mode_t CONTROL_get_monaural_mode(void){
    return PCM_get_monaural_mode();
}

CONTROL_zero_detection_t CONTROL_get_zero_detection(void){
    return (PCM_get_left_zero_detection() + (2 * PCM_get_rigth_zero_detection()));
}

//== only SRC related ==========================================================