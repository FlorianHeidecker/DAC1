/** 
 * @file        PCM_API.c
 *
 * @brief       PCM_API contains the PLL basic functions
 *
 * This Module implements the PLL basis functionalities. The Module contains
 * functions to set the PLL output frequencys.
 * 
 * @author      Florian Heidecker
 * @date        26.11.2015 - initial version
 * 
 * @version     0.1
 *
 */
 
#ifndef _PCM_API_H
#define _PCM_API_H

#include <xc.h>

#define disabled    0
#define enabled     1

//== typedefs ==================================================================

/** avalible Audio Data Format Selection */
typedef enum {	PCM_16_bit_standard_format=0,
				PCM_20_bit_standard_format=1,
				PCM_24_bit_standard_format=2,
				PCM_16_bit_MSB_first=3,
				PCM_16_bit_I2S=4,
				PCM_24_bit_I2S=5} audio_data_format_t;
                
/** avalible Delta-Sigma Oversampling Rate Selection */
typedef enum {	PCM_64_times_fs=0,
				PCM_32_times_fs=1,
				PCM_128_times_fs=2} oversampling_rate_t;

/** define mode_t */
typedef enum {stereo = 0, mono = 1} mode_t;

/** define channel_t */
typedef enum {L_channel = 0, R_channel = 1} channel_t;

//== functions =================================================================

void pcm_init(void);

// improved send and receive function
uint8_t send_receive(uint8_t address, uint8_t data);

/** ATL/ATR: Digital Attenuation Level Setting 
    read and write
	stepsize = -0,5 dB
	DEC value		Attenuation Level
	0 - 240			0 dB - (-120,0) dB
	241 - 255		MUTE
*/
void set_attunation_level_left(uint8_t value);

uint8_t get_attunation_level_left(void);

void set_attunation_level_right(uint8_t value);

uint8_t get_attunation_level_right(void);

/** ATS: Attenuation Rate Select 
    read and write */
//void set_????

/** ATLD: Attenuation Load Control 
    read and write */
void set_attenuation_control(uint8_t value);

uint8_t get_attenuation_control(void);

/** FMT: Audio Interface Data Format 
    read and write */
void set_audio_data_format(audio_data_format_t);

audio_data_format_t get_audio_data_format(void);

/** DMF: Sampling Frequency Selection for the De-Emphasis Function 
    read and write */
//void set_de_emphasis_freq(de_emphasis_freq_t)

/** OS: Delta-Sigma Oversampling Rate Selection 
    read and write */
void set_oversampling_rate(oversampling_rate_t);

oversampling_rate_t get_oversampling_rate(void);

/** DME: Digital De-Emphasis Control 
    read and write */
//void set_de_emphasis_control(int);

/** MUTE: Soft Mute Control 
    read and write */
void set_soft_mute(uint8_t value);

uint8_t get_soft_mute(void);

/** REV: Output Phase Reversal 
    read and write */
//void set_out_phase_reversal(int);

/** OPE: DAC Operation Control 
    read and write */
//void set_DAC_operation(int);

/** FLT: Digital Filter Rolloff Control 
    read and write */
//void set_filter_rolloff(filter_rolloff_t);

/** INZD: Infinite Zero Detect Mute Control 
    read and write */
void set_zero_detect_mute(uint8_t value);

uint8_t get_zero_detect_mute(void);

/** SRST: System Reset Control 
    read and write */
void set_pcm_reset(uint8_t value);

uint8_t get_pcm_reset(void);

/** DSD: DSD Interface Mode Control 
    read and write */
//void set_DSD_interface_mode(int);

/** DFTH: Digital Filter Bypass (or Through Mode) Control 
    read and write */
//void set_digital_filter_bypass(int);

/** MONO: Monaural Mode Selection */
//void set_mode(mode_t);

/** CHSL: Channel Selection for Monaural Mode 
    read and write */
//void set_used_mono_channel(channel_t)

/** DZ: DSD Zero Output Enable 
    read and write */
//void set_DSD_zero_output(DSD_zero_output_t);

/** PCMZ: PCM Zero Output Enable 
    read and write */
//void set_PCM_zero_output(int);

/** ZFGL/ZFGR: Zero-Detection Flag 
    read pmly */
uint8_t get_left_zero_detection(void);

uint8_t get_rigth_zero_detection(void);

/** ID: Device ID 
    read only */
//int get_device_id(void);

#endif /* _PCM_API_H */


