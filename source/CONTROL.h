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

/**
 * @brief set default configuration for all settings
 */
void CONTROL_init(void);

/**
 * @ brief set specific oversampling frequency
 * 
 * @param CONTROL_oversampling_freq
 *              - CONTROL_OVERSAMPLING_FREQ_32kHz
 *              - CONTROL_OVERSAMPLING_FREQ_44_1kHz
 *              - CONTROL_OVERSAMPLING_FREQ_48kHz
 *              - CONTROL_OVERSAMPLING_FREQ_64kHz
 *              - CONTROL_OVERSAMPLING_FREQ_88_2kHz
 *              - CONTROL_OVERSAMPLING_FREQ_96kHz
 *              - CONTROL_OVERSAMPLING_FREQ_192kHz
 */
void CONTROL_set_oversampling_freq(CONTROL_oversampling_freq_t CONTROL_oversampling_freq);

/**
 * @brief get the selected oversampling frequency
 * 
 * @return
 *      - CONTROL_OVERSAMPLING_FREQ_32kHz
 *      - CONTROL_OVERSAMPLING_FREQ_44_1kHz
 *      - CONTROL_OVERSAMPLING_FREQ_48kHz
 *      - CONTROL_OVERSAMPLING_FREQ_64kHz
 *      - CONTROL_OVERSAMPLING_FREQ_88_2kHz
 *      - CONTROL_OVERSAMPLING_FREQ_96kHz
 *      - CONTROL_OVERSAMPLING_FREQ_192kHz
 */
CONTROL_oversampling_freq_t CONTROL_get_oversampling_freq(void);

/**
 * @brief set audio date format
 * 
 * @param CONTROL_audio_data_format
 *              - CONTROL_16_bit_standard_format
 *              - CONTROL_20_bit_standard_format
 *              - CONTROL_24_bit_standard_format
 *              - CONTROL_24_bit_MSB_first
 *              - CONTROL_24_bit_I2S
 */
void CONTROL_set_audio_data_format(CONTROL_audio_data_format_t CONTROL_audio_data_format);

/**
 * @brief get selected audio data format
 * 
 * @return
 *      - CONTROL_16_bit_standard_format
 *      - CONTROL_20_bit_standard_format
 *      - CONTROL_24_bit_standard_format
 *      - CONTROL_24_bit_MSB_first
 *      - CONTROL_24_bit_I2S
 */
CONTROL_audio_data_format_t CONTROL_get_audio_data_format(void);

/**
 * @brief Reset for SRC and PCM
 */
void CONTROL_reset(void);

/**
 * @brief Set attenuation level. The function for both
 *        separate channels were combined and the possible
 *        levels were reduced to an useful number. 100%
 *        corresponds to 0 dB and 0% corresponds to -60dB.
 * 
 * @param percent
 *      0-100 (percent)
 *          0 corresponds to -60dB
 *          100 corresponds to 0 dB
 */
void CONTROL_set_attunation_level(uint16_t percent);

/**
 * @brief get the actual attenuation level
 * 
 * @return
 *      0-100 (percent)
 *          0 corresponds to -60dB
 *          100 corresponds to 0 dB
 */
uint16_t CONTROL_get_attunation_level(void);

/**
 * @brief Set soft mute. If enabled audio output will be
 *        muted after 256-steps of the operating attenuator.
 *        The attenuator is decremented/ incremented during
 *        every Left-Right-Clock transition.
 * 
 * @param value
 *        PCM_disabled
 *        PCM_enabled
 */
void CONTROL_set_soft_mute(uint16_t value);

/**
 * @brief get actual state of soft mute
 * 
 * @return 
 *        PCM_disabled
 *        PCM_enabled
 */
uint16_t CONTROL_get_soft_mute(void);

/**
 * @brief Set zero detect mute. If PCM1791A detects
 *        a zero condition in both channels, outputs will muted
 * 
 * @param value
 *        PCM_disabled
 *        PCM_enabled
 */
void CONTROL_set_zero_detect_mute(uint16_t value);

/**
 * @brief get actual state of zero detect mute
 * 
 * @return 
 *        PCM_disabled
 *        PCM_enabled
 */
uint16_t CONTROL_get_zero_detect_mute(void);

/**
 * @brief set monaural or stereo mode
 * 
 * @param PCM_monaural_mode
 *        PCM_stereo
 *        PCM_mono
 */
void CONTROL_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode);

/**
 * @brief get selected mode
 * 
 * @return 
 *        PCM_stereo
 *        PCM_mono
 */
PCM_monaural_mode_t CONTROL_get_monaural_mode(void);

/**
 * @brief get info about, which channel is zero
 * 
 * @return 
 *      no_zero_detection
 *      left_zero_detection
 *      right_zero_detection
 *      left_right_zero_detection
 */
CONTROL_zero_detection_t CONTROL_get_zero_detection(void);

#endif	/* _CONTROL_H */

