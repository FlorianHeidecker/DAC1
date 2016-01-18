/** 
 * @file        PCM_API.h
 *
 * @brief       PCM_API contains IC basic functions
 * 
 * @author      Florian Heidecker
 * @date        26.11.2015 - initial version
 *              07.12.2015 - rework/comments
 * 
 * @version     0.1
 */
 
#ifndef _PCM_API_H
#define _PCM_API_H

#include <xc.h>

//== typedefs ==================================================================

#define PCM_disabled 0
#define PCM_enabled  1

/** PCM: avalible audio data format selection */
typedef enum {	PCM_16_bit_standard_format=0,
				PCM_20_bit_standard_format=1,
				PCM_24_bit_standard_format=2,
				PCM_24_bit_MSB_first=3,
				PCM_16_bit_I2S=4,
				PCM_24_bit_I2S=5} PCM_audio_data_format_t;
                
/** PCM: avalible delta-sigma oversampling rate selection */
typedef enum {	PCM_64_times_fs=0,
				PCM_32_times_fs=1,
				PCM_128_times_fs=2} PCM_oversampling_rate_t;

/** PCM: monaural mode selection */
typedef enum {PCM_stereo = 0, PCM_mono = 1} PCM_monaural_mode_t;

/** PCM: select data channel for PCM_mono mode */
typedef enum {PCM_left_channel = 0, PCM_right_channel = 1} PCM_data_channel_t;

//== functions =================================================================

/**
 * @brief           improved send and receive function for pcm
 * 
 * @param address   register to write or read
 * @param data      write data
 * @param           read_write (write = 0, read = 1)
 * @return          read data
 */
uint8_t PCM_send_receive(uint8_t address, uint8_t data, uint8_t read_write);

/**
 * @brief           set digital attenuation level, left side
 *                  PCM_set_attenuation_control  must be set to 1 
 *                  in order to change the attenuation level.
 * 
 * @param value     stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  15 - 255		(-120,0) - dB 0 dB
 *                  0 - 14          mute
 */
void PCM_set_attenuation_level_left(uint16_t value);

/**
 * @brief           get digital attenuation level, left side
 * 
 * @return          stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  15 - 255		(-120,0) - dB 0 dB
 *                  0 - 14          mute
 */
uint16_t PCM_get_attenuation_level_left(void);

/**
 * @brief           set digital attenuation level, right side
 *                  PCM_set_attenuation_control  must be set to 1 
 *                  in order to change the attenuation level.
 * 
 * @param value     stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  15 - 255		(-120,0) - dB 0 dB
 *                  0 - 14          mute
 */
void PCM_set_attenuation_level_right(uint16_t value);

/**
 * @brief           get digital attenuation level, right side
 * 
 * @return          stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  15 - 255		(-120,0) - dB 0 dB
 *                  0 - 14          mute
 */
uint16_t PCM_get_attenuation_level_right(void);

/**
 * @brief           soft mute control
 * 
 * @param value     PCM_disabled/PCM_enabled
 */
void PCM_set_soft_mute(uint16_t value);

/**
 * @brief           soft mute control
 * 
 * @return          PCM_disabled/PCM_enabled
 */
uint16_t PCM_get_soft_mute(void);

/**
 * @brief           set Attenuation Load Control (ALC)
 *                  ALC must be set to 1 in order to change the attenuation
 *                  level.
 *                  If ALC = 0 attenuation level remain at the previously
 *                  programmed levels, ignoring new data.
 * 
 * @param value     disabled/enabeld
 */
void PCM_set_attenuation_control(uint16_t value);

/**
 * @brief           get Attenuation Load Control (ALC)
 *                  ALC must be set to 1 in order to change the attenuation
 *                  level.
 *                  If ALC = 0 attenuation level remain at the previously
 *                  programmed levels, ignoring new data.
 * 
 * @return          disabled/enabeld
 */
uint16_t PCM_get_attenuation_control(void);

/**
 * @brief           set data format for the audio data interface
 * 
 * @param PCM_audio_data_format
 *                  PCM_16_bit_standard_format
 *                  PCM_20_bit_standard_format
 *                  PCM_24_bit_standard_format
 *                  PCM_24_bit_MSB_first
 *                  PCM_16_bit_I2S
 *                  PCM_24_bit_I2S
 */
void PCM_set_audio_data_format(PCM_audio_data_format_t PCM_audio_data_format);

/**
 * @brief           get the selected audio data format
 * 
 * @return 
 *                  PCM_16_bit_standard_format
 *                  PCM_20_bit_standard_format
 *                  PCM_24_bit_standard_format
 *                  PCM_24_bit_MSB_first
 *                  PCM_16_bit_I2S
 *                  PCM_24_bit_I2S
 */
PCM_audio_data_format_t PCM_get_audio_data_format(void);

/**
 * @brief           The function changes the oversampling rate of
 *                  delta-sigma modulation. This allows the use of
 *                  only a single type (cutoff frequency) of post
 *                  low-pass filter. Set 128 times in 44.1-kHz
 *                  operation, 64 times in 96-kHz operation, and 32
 *                  times in 192-kHz. The 128 fS oversampling rate
 *                  is not available at sampling rates above 100 kHz
 *                  and a system clock of more than 256 fS is required.
 * 
 * @param PCM_oversampling_rate
 *                  PCM_64_times_fs
 *                  PCM_32_times_fs
 *                  PCM_128_times_fs
 */
void PCM_set_oversampling_rate(PCM_oversampling_rate_t PCM_oversampling_rate);

/**
 * @brief           get selected oversampling rate
 * 
 * @return          
 *                  PCM_64_times_fs
 *                  PCM_32_times_fs
 *                  PCM_128_times_fs
 */
PCM_oversampling_rate_t PCM_get_oversampling_rate(void);

/** FLT: Digital Filter Rolloff Control */
//void set_filter_rolloff(filter_rolloff_t);

/**
 * @brief           set infinite zero detect mute control
 *                  if 1, forces muted analog outputs to hold a bipolar zero
 *                  level when the PCM1791A detects a zero condition in both
 *                  channels.
 * 
 * @param value     PCM_disabled/PCM_enabled
 */
void PCM_set_zero_detect_mute(uint16_t value);

/**
 * @brief           get actual state of zero detect mute
 * 
 * @return          PCM_disabled/PCM_enabled
 */
uint16_t PCM_get_zero_detect_mute(void);

/**
 * @brief           system reset control 
 *                  resets the PCM1791A to the initial system condition.
 * 
 * @param value     Normal operation = 0,
 *                  System reset operation = 1 (generate one reset pulse)
 */
void PCM_reset(uint16_t value);

/**
 * @brief           set monaural or stereo mode
 * 
 * @param PCM_acoustics_mode    
 *                  PCM_stereo
 *                  PCM_mono

 */
void PCM_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode);

/**
 * @brief           get selected mode
 * 
 * @return          
 *                  PCM_stereo
 *                  PCM_mono
 */
PCM_monaural_mode_t PCM_get_monaural_mode(void);

/**
 * @brief           Selected input channel for monaural mode
 * 
 * @param PCM_data_channel
 *                  PCM_left_channel
 *                  PCM_right_channel
 */
void PCM_set_data_channel(PCM_data_channel_t PCM_data_channel);

/**
 * @brief           get selected input channel for monaural mode
 * 
 * @return          
 *                  PCM_left_channel
 *                  PCM_right_channel
 */
PCM_data_channel_t PCM_get_data_channel(void);

/**
 * @brief           zero detect in output channel, left
 * 
 * @return          not zero = 0, zero detect = 1
 */
uint16_t PCM_get_left_zero_detection(void);

/**
 * @brief           zero detect in output channel, right
 * 
 * @return          not zero = 0, zero detect = 1
 */
uint16_t PCM_get_rigth_zero_detection(void);

#endif /* _PCM_API_H */


