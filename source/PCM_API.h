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
 * @return          read data
 */
uint8_t PCM_send_receive(uint8_t address, uint8_t data);

/**
 * @brief           set digital attenuation level, left side
 *                  ATLD must be set to 1 in order to change the attenuation
 *                  level.
 * 
 * @param value     stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  0 - 240			0 dB - (-120,0) dB
 *                  241 - 255		mute
 */
void PCM_set_attunation_level_left(uint8_t value);

/**
 * @brief           get digital attenuation level, left side
 * 
 * @return          stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  0 - 240			0 dB - (-120,0) dB
 *                  241 - 255		mute
 */
uint8_t PCM_get_attunation_level_left(void);

/**
 * @brief           set digital attenuation level, right side
 *                  ATLD must be set to 1 in order to change the attenuation
 *                  level.
 * 
 * @param value     stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  0 - 240			0 dB - (-120,0) dB
 *                  241 - 255		mute
 */
void PCM_set_attunation_level_right(uint8_t value);

/**
 * @brief           get digital attenuation level, right side
 * 
 * @return          stepsize = -0,5 dB
 *                  dec value		attenuation level
 *                  0 - 240			0 dB - (-120,0) dB
 *                  241 - 255		mute
 */
uint8_t PCM_get_attunation_level_right(void);

/** ATS: Attenuation Rate Select 
    read and write */
//void set_????

/**
 * @brief           soft mute control
 * 
 * @param value     disabled/enabeld
 */
void set_soft_mute(uint8_t value);

/**
 * @brief           soft mute control
 * 
 * @return          disabled/enabeld
 */
uint8_t get_soft_mute(void);

/**
 * @brief           set ATLD: attenuation load control
 *                  ATLD must be set to 1 in order to change the attenuation
 *                  level.
 *                  If ATLD = 0 attenuation level remain at the previously
 *                  programmed levels, ignoring new data.
 * 
 * @param value     disabled/enabeld
 */
void PCM_set_attenuation_control(uint8_t value);

/**
 * @brief           get ATLD: attenuation load control
 *                  ATLD must be set to 1 in order to change the attenuation
 *                  level.
 *                  If ATLD = 0 attenuation level remain at the previously
 *                  programmed levels, ignoring new data.
 * 
 * @return          disabled/enabeld
 */
uint8_t PCM_get_attenuation_control(void);

/**
 * @brief           set audio interface data format
 * 
 * @param PCM_audio_data_format     see
 *                                  PCM: avalible audio data format selection
 *                                  -> PCM_audio_data_format_t
 */
void PCM_set_audio_data_format(PCM_audio_data_format_t PCM_audio_data_format);

/**
 * @brief           get audio interface data format
 * 
 * @return          see
 *                  PCM: avalible audio data format selection
 *                  -> PCM_audio_data_format_t
 */
PCM_audio_data_format_t PCM_get_audio_data_format(void);

/**
 * @brief           set delta-sigma oversampling rate selection
 *                  allows the use of only a single type (cutoff frequency)
 *                  of post low-pass filter. If the 128-fS oversampling rate
 *                  is selected, a system clock of more than 256 fS is required.
 * 
 * @param PCM_oversampling_rate     see
 *                                  PCM: avalible delta-sigma oversampling
 *                                  rate selection
 *                                  -> PCM_oversampling_rate_t
 *                                  set 128 times in 44.1-kHz operation,
 *                                  64 times in 96-kHz operation,
 *                                  32 times in 192-kHz operation
 */
void PCM_set_oversampling_rate(PCM_oversampling_rate_t PCM_oversampling_rate);

/**
 * @brief           get delta-sigma oversampling rate selection
 *                  allows the use of only a single type (cutoff frequency)
 *                  of post low-pass filter. If the 128-fS oversampling rate
 *                  is selected, a system clock of more than 256 fS is required.
 * 
 * @return          see
 *                  PCM: avalible delta-sigma oversampling
 *                  rate selection
 *                  -> PCM_oversampling_rate_t
 *                  set 128 times in 44.1-kHz operation,
 *                  64 times in 96-kHz operation,
 *                  32 times in 192-kHz operation
 */
PCM_oversampling_rate_t PCM_get_oversampling_rate(void);

/** DMF: Sampling Frequency Selection for the De-Emphasis Function 
    read and write */
//void set_de_emphasis_freq(de_emphasis_freq_t)

/** DME: Digital De-Emphasis Control 
    read and write */
//void set_de_emphasis_control(int);

/** REV: Output Phase Reversal 
    read and write */
//void set_out_phase_reversal(int);

/** OPE: DAC Operation Control 
    read and write */
//void set_DAC_operation(int);

/** FLT: Digital Filter Rolloff Control 
    read and write */
//void set_filter_rolloff(filter_rolloff_t);

/**
 * @brief           set infinite zero detect mute control
 *                  if 1, forces muted analog outputs to hold a bipolar zero
 *                  level when the PCM1791A detects a zero condition in both
 *                  channels.
 * 
 * @param value     disabled/enabeld
 */
void PCM_set_zero_detect_mute(uint8_t value);

/**
 * @brief           get infinite zero detect mute control
 *                  if 1, forces muted analog outputs to hold a bipolar zero
 *                  level when the PCM1791A detects a zero condition in both
 *                  channels.
 * 
 * @return          disabled/enabeld
 */
uint8_t PCM_get_zero_detect_mute(void);

/**
 * @brief           system reset control 
 *                  resets the PCM1791A to the initial system condition.
 * 
 * @param value     Normal operation = 0,
 *                  System reset operation = 1 (generate one reset pulse)
 */
void PCM_pcm_reset(uint8_t value);

/** DSD: DSD Interface Mode Control 
    read and write */
//void set_DSD_interface_mode(int);

/** DFTH: Digital Filter Bypass (or Through Mode) Control 
    read and write */
//void set_digital_filter_bypass(int);

/**
 * @brief           set monaural mode selection
 * 
 * @param PCM_acoustics_mode    see
 *                              PCM: monaural mode selection
 *                              -> PCM_monaural_mode_t
 */
void PCM_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode);

/**
 * @brief           get monaural mode selection
 * 
 * @return          see
 *                  PCM: monaural mode selection
 *                  -> PCM_monaural_mode_t
 */
PCM_monaural_mode_t PCM_get_monaural_mode(void);

/**
 * @brief           set channel selection for monaural mode, select data input
 *                  channel
 * 
 * @param PCM_data_channel      see
 *                              PCM: select data channel for PCM_mono mode
 *                              -> PCM_data_channel_t
 */
void PCM_set_data_channel(PCM_data_channel_t PCM_data_channel);

/**
 * @brief           get channel selection for monaural mode, select data input
 *                  channel
 * 
 * @return          see
 *                  PCM: select data channel for PCM_mono mode
 *                  -> PCM_data_channel_t
 */
PCM_data_channel_t PCM_get_data_channel(void);

/** DZ: DSD Zero Output Enable 
    read and write */
//void set_DSD_zero_output(DSD_zero_output_t);

/** PCMZ: PCM Zero Output Enable 
    read and write */
//void set_PCM_zero_output(int);

/** ZFGL/ZFGR: Zero-Detection Flag 
    read pmly */

/**
 * @brief           zero detect in output channel, left
 * 
 * @return          not zero = 0, zero detect = 1
 */
uint8_t PCM_get_left_zero_detection(void);

/**
 * @brief           zero detect in output channel, right
 * 
 * @return          not zero = 0, zero detect = 1
 */
uint8_t PCM_get_rigth_zero_detection(void);

/** ID: Device ID 
    read only */
//int get_device_id(void);

#endif /* _PCM_API_H */


