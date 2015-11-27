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

#include <xc.h>

#include "log.h"
#include "PCM_API.h"
#include "SPI_API.h"

#define pcm_channel_dummy       333 //!!!!!!!!!!!!!!!!!!!!

/** avalible Register 16 - 23 */
typedef enum {	PCM_register_16_w = 0x10,   PCM_register_16_r = 0x90,
                PCM_register_17_w = 0x11,   PCM_register_17_r = 0x91,
                PCM_register_18_w = 0x12,   PCM_register_18_r = 0x92,
				PCM_register_19_w = 0x13,   PCM_register_19_r = 0x93,
				PCM_register_20_w = 0x14,   PCM_register_20_r = 0x94,
                PCM_register_21_w = 0x15,   PCM_register_21_r = 0x95,
                                            PCM_register_22_r = 0x96,
                                            PCM_register_23_r = 0x97} pcm_register_t;

void pcm_init(void){
    PCM_LOG("PLL init\n");
}

uint8_t send_receive(uint8_t address, uint8_t data){
    uint8_t data_send[2] = {address, data};
    uint8_t data_receive[2] = {0, 0};
    
    spi_rw_n(data_send, data_receive, 2, pcm_channel_dummy);
    
    return *(data_receive + 1);
}

void set_attunation_level_left(uint8_t value){
    PCM_LOG("Attenuation Level: %i", ~value);
    send_receive(PCM_register_16_w, ~value);
}

uint8_t get_attunation_level_left(void){
    return send_receive(PCM_register_16_r, 0x00);
}

void set_attunation_level_right(uint8_t value){
    PCM_LOG("Attenuation Level: %i", ~value);
    send_receive(PCM_register_17_w, ~value);
}

uint8_t get_attunation_level_right(void){
    return send_receive(PCM_register_17_r, 0x00);
}

void set_attenuation_control(uint8_t value){
    uint8_t data = send_receive(PCM_register_18_r, 0x00);
    data ^= (-value ^ data) & (1 << 7);
    send_receive(PCM_register_18_w, data);
}

uint8_t get_attenuation_control(void){
    uint8_t data = send_receive(PCM_register_18_r, 0x00);
    return (data >> 7) & 1;
}

void set_audio_data_format(audio_data_format_t audio_data_format){
    uint8_t data = send_receive(PCM_register_18_r, 0x00);
    
    switch(audio_data_format){
        case PCM_16_bit_standard_format:
            data &= ~(1 << 4);
            data &= ~(1 << 5);
            data &= ~(1 << 6);
            break;
        case PCM_20_bit_standard_format:
            data |= 1 << 4;
            data &= ~(1 << 5);
            data &= ~(1 << 6);
            break;
		case PCM_24_bit_standard_format:
            data &= ~(1 << 4);
            data |= 1 << 5;
            data &= ~(1 << 6);
            break;
		case PCM_16_bit_MSB_first:
            data |= 1 << 4;
            data |= 1 << 5;
            data &= ~(1 << 6);
            break;
		case PCM_16_bit_I2S:
            data &= ~(1 << 4);
            data &= ~(1 << 5);
            data |= 1 << 6;
            break;
		case PCM_24_bit_I2S:
            data |= 1 << 4;
            data &= ~(1 << 5);
            data |= 1 << 6;
            break;
    }
    
    send_receive(PCM_register_18_w, data);
}

audio_data_format_t get_audio_data_format(void){
    uint8_t data = send_receive(PCM_register_18_r, 0x00);
    uint8_t bit_4 = (data >> 4) & 1;
    uint8_t bit_5 = (data >> 5) & 1;
    uint8_t bit_6 = (data >> 6) & 1;
    return (4 * bit_6 + 2 * bit_5 + bit_4);
}

void set_oversampling_rate(oversampling_rate_t oversampling_rate){
    uint8_t data = send_receive(PCM_register_20_r, 0x00);
    
    switch(oversampling_rate){
        case PCM_64_times_fs:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            break;
        case PCM_32_times_fs:
            data |= 1 << 0;
            data &= ~(1 << 1);
            break;
		case PCM_128_times_fs:
            data &= ~(1 << 0);
            data |= 1 << 1;
            break;
    }
    
    send_receive(PCM_register_18_w, data);
}

oversampling_rate_t get_oversampling_rate(void){
    uint8_t data = send_receive(PCM_register_18_r, 0x00);
    uint8_t bit_0 = (data >> 0) & 1;
    uint8_t bit_1 = (data >> 1) & 1;
    return (2 * bit_1 + bit_0);
}

void set_soft_mute(uint8_t value){
    uint8_t data = send_receive(PCM_register_18_r, 0x00);
    data ^= (-value ^ data) & (1 << 0);
    send_receive(PCM_register_18_w, data);
}

uint8_t get_soft_mute(void){
    uint8_t data = send_receive(PCM_register_18_r, 0x00);
    return ((data >> 0) & 1);
}

void set_zero_detect_mute(uint8_t value){
    uint8_t data = send_receive(PCM_register_19_r, 0x00);
    data ^= (-value ^ data) & (1 << 0);
    send_receive(PCM_register_19_w, data);
}

uint8_t get_zero_detect_mute(void){
    uint8_t data = send_receive(PCM_register_19_r, 0x00);
    return ((data >> 0) & 1);
}

void set_pcm_reset(uint8_t value){
    uint8_t data = send_receive(PCM_register_20_r, 0x00);
    data ^= (-value ^ data) & (1 << 6);
    send_receive(PCM_register_20_w, data);
}

uint8_t get_pcm_reset(void){
    uint8_t data = send_receive(PCM_register_20_r, 0x00);
    return ((data >> 6) & 1);
}

uint8_t get_left_zero_detection(void){
    uint8_t data = send_receive(PCM_register_22_r, 0x00);
    return ((data >> 0) & 1);
}

uint8_t get_rigth_zero_detection(void){
    uint8_t data = send_receive(PCM_register_22_r, 0x00);
    return ((data >> 1) & 1);
}