/** 
 * @file        PCM_API.c
 *
 * @brief       PCM_API contains IC basic functions
 * 
 * @author      Florian Heidecker
 * @date        26.11.2015 - initial version
 *              07.12.2015 - rework/comments
 * 
 * @version     0.1
 */

#include <xc.h>

#include "log.h"
#include "PCM_API.h"
#include "SPI_API.h"

#define WRITE 0
#define READ 1

/** PCM: avalible Register 16 - 23 */
typedef enum {	PCM_register_16 = 0x10,
                PCM_register_17 = 0x11,
                PCM_register_18 = 0x12,
                PCM_register_19 = 0x13,
                PCM_register_20 = 0x14,
                PCM_register_21 = 0x15,
                PCM_register_22 = 0x16,
                PCM_register_23 = 0x17} PCM_register_t;

uint8_t PCM_send_receive(uint8_t address, uint8_t data, uint8_t read_write){
    if(read_write == 1){ // if read, set 1
        address |= 1 << 7;
    }
    uint8_t data_send[2] = {address, data};
    uint8_t data_receive[2] = {0, 0};
    
    PCM_LOG("PCM send: Register: 0x%x || Data: 0x%x\n", *data_send, *(data_send + 1));
    spi_rw_n(data_send, data_receive, 2, SPI_DAC_channel);
    PCM_LOG("PCM receive: Data[0]: 0x%x || Data[1]: 0x%x\n", address, *(data_receive + 1));
    
    return *(data_receive + 1);
}

void PCM_set_attenuation_level_left(uint8_t value){
    PCM_send_receive(PCM_register_16, value, WRITE);
}

uint8_t PCM_get_attenuation_level_left(void){
    return PCM_send_receive(PCM_register_16, 0x00, READ);
}

void PCM_set_attenuation_level_right(uint8_t value){
    PCM_send_receive(PCM_register_17, value, WRITE);
}

uint8_t PCM_get_attenuation_level_right(void){
    return PCM_send_receive(PCM_register_17, 0x00, READ);
}

void PCM_set_soft_mute(uint8_t value){
    uint8_t data = PCM_send_receive(PCM_register_18, 0x00, READ);
    data ^= (-value ^ data) & (1 << 0);
    PCM_send_receive(PCM_register_18, data, WRITE);
}

uint8_t PCM_get_soft_mute(void){
    uint8_t data = PCM_send_receive(PCM_register_18, 0x00, READ);
    return ((data >> 0) & 1);
}

void PCM_set_attenuation_control(uint8_t value){
    uint8_t data = PCM_send_receive(PCM_register_18, 0x00, READ);
    data ^= (-value ^ data) & (1 << 7);
    PCM_send_receive(PCM_register_18, data, WRITE);
}

uint8_t PCM_get_attenuation_control(void){
    uint8_t data = PCM_send_receive(PCM_register_18, 0x00, READ);
    return (data >> 7) & 1;
}

void PCM_set_audio_data_format(PCM_audio_data_format_t PCM_audio_data_format){
    uint8_t data = PCM_send_receive(PCM_register_18, 0x00, READ);
    
    switch(PCM_audio_data_format){
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
		case PCM_24_bit_MSB_first:
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
    
    PCM_send_receive(PCM_register_18, data, WRITE);
}

PCM_audio_data_format_t PCM_get_audio_data_format(void){
    uint8_t data = PCM_send_receive(PCM_register_18, 0x00, READ);
    return (data >> 4) & 0x7;
}

void PCM_set_oversampling_rate(PCM_oversampling_rate_t PCM_oversampling_rate){
    uint8_t data = PCM_send_receive(PCM_register_20, 0x00, READ);
    
    switch(PCM_oversampling_rate){
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
    
    PCM_send_receive(PCM_register_20, data, WRITE);
}

PCM_oversampling_rate_t PCM_get_oversampling_rate(void){
    uint8_t data = PCM_send_receive(PCM_register_20, 0x00, READ);
    return (data >> 0) & 0x3;
}

void PCM_set_zero_detect_mute(uint8_t value){
    uint8_t data = PCM_send_receive(PCM_register_19, 0x00, READ);
    data ^= (-value ^ data) & (1 << 0);
    PCM_send_receive(PCM_register_19, data, WRITE);
}

uint8_t PCM_get_zero_detect_mute(void){
    uint8_t data = PCM_send_receive(PCM_register_19, 0x00, READ);
    return ((data >> 0) & 1);
}

void PCM_set_pcm_reset(uint8_t value){
    uint8_t data = PCM_send_receive(PCM_register_20, 0x00, READ);
    data ^= (-value ^ data) & (1 << 6);
    PCM_send_receive(PCM_register_20, data, WRITE);
}

void PCM_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode){
    uint8_t data = PCM_send_receive(PCM_register_20, 0x00, READ);
    data ^= (-PCM_monaural_mode ^ data) & (1 << 3);
    PCM_send_receive(PCM_register_20, data, WRITE);
}

PCM_monaural_mode_t PCM_get_monaural_mode(void){
    uint8_t data = PCM_send_receive(PCM_register_20, 0x00, READ);
    return ((data >> 3) & 1);
}

void PCM_set_data_channel(PCM_data_channel_t PCM_data_channel){
    uint8_t data = PCM_send_receive(PCM_register_20, 0x00, READ);
    data ^= (-PCM_data_channel ^ data) & (1 << 2);
    PCM_send_receive(PCM_register_20, data, WRITE);
}

PCM_data_channel_t PCM_get_data_channel(void){
    uint8_t data = PCM_send_receive(PCM_register_20, 0x00, READ);
    return ((data >> 2) & 1);
}

uint8_t PCM_get_left_zero_detection(void){
    uint8_t data = PCM_send_receive(PCM_register_22, 0x00, READ);
    return ((data >> 0) & 1);
}

uint8_t PCM_get_rigth_zero_detection(void){
    uint8_t data = PCM_send_receive(PCM_register_22, 0x00, READ);
    return ((data >> 1) & 1);
}
