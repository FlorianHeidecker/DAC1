/** 
 * @file        CONTROL.h
 *
 * @brief       CONTROL controls all input and output set and get function
 * 
 * @author      Florian Heidecker
 * @date        07.12.2015 - initial version
 *              08.12.2015 - PCM function implementation
 * 
 * @version     0.1
 */

#ifndef _CONTROL_H
#define	_CONTROL_H

#include <xc.h>
#include "PCM_API.h"

//== typedefs ==================================================================
typedef enum {	no_zero_detection=0,
				left_zero_detection=1,
				right_zero_detection=2,
				left_right_zero_detection=3} CONTROL_zero_detection_t;

#define bottom_border_level 135

typedef enum {	CONTROL_16_bit_standard_format=0,
				CONTROL_20_bit_standard_format,
				CONTROL_24_bit_standard_format,
				CONTROL_24_bit_MSB_first,
				CONTROL_24_bit_I2S} CONTROL_audio_data_format_t;

typedef enum {  CONTROL_OVERSAMPLING_FREQ_32kHz=0,
                CONTROL_OVERSAMPLING_FREQ_44_1kHz,
                CONTROL_OVERSAMPLING_FREQ_48kHz,
                CONTROL_OVERSAMPLING_FREQ_64kHz,
                CONTROL_OVERSAMPLING_FREQ_88_2kHz,
                CONTROL_OVERSAMPLING_FREQ_96kHz,
                CONTROL_OVERSAMPLING_FREQ_192kHz} CONTROL_oversampling_freq_t;

//== functions =================================================================

void CONTROL_init(void);

void CONTROL_set_oversampling_freq(CONTROL_oversampling_freq_t CONTROL_oversampling_freq);

CONTROL_oversampling_freq_t CONTROL_get_oversampling_freq(void);

void CONTROL_set_audio_data_format(CONTROL_audio_data_format_t CONTROL_audio_data_format);

CONTROL_audio_data_format_t CONTROL_get_audio_data_format(void);

void CONTROL_reset(void);

void CONTROL_set_attunation_level(uint16_t percent);

uint16_t CONTROL_get_attunation_level(void);

void CONTROL_set_soft_mute(uint16_t value);

uint16_t CONTROL_get_soft_mute(void);

void CONTROL_set_zero_detect_mute(uint16_t value);

uint16_t CONTROL_get_zero_detect_mute(void);

void CONTROL_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode);

PCM_monaural_mode_t CONTROL_get_monaural_mode(void);

CONTROL_zero_detection_t CONTROL_get_zero_detection(void);

#endif	/* _CONTROL_H */
