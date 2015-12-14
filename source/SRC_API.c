/** 
 * @file        SRC_API.h
 *
 * @brief       SRC_API contains IC basic functions
 * 
 * @author      Marco Jost
 * @date        08.12.2015 - first version
 *              
 * 
 * @version     0.1
 */

#include <xc.h>

#include "log.h"
#include "SRC_API.h"
#include "SPI_API.h"


void SRC_send (uint8_t address, uint8_t data){
    uint8_t data_send[3] = {address, 0, data};
    uint8_t data_receive[3] = {0, 0, 0};
    
    SRC_LOG("SRC send: Register: 0x%x || Data: 0x%x\n", address, *(data_send + 2));
    spi_rw_n(data_send, data_receive, 3, SPI_SRC_channel);
}

 uint8_t SRC_receive (uint8_t address){
    address |= (1 << 7);    //maybe global define address_read_bit for src and pcm
    uint8_t data_send[3] = {address, 0, 0};
    uint8_t data_receive[3] = {0, 0, 0};
    
    spi_rw_n(data_send, data_receive, 3, SPI_SRC_channel);
    SRC_LOG("SRC receive: Register: 0x%x || Data: 0x%x\n", address, *(data_receive + 2));
    
    return *(data_receive + 2);
 }

void SRC_init (void){
    uint8_t data = 0x3F; // enable all fuction blocks on SRC
    SRC_send(SRC_register_power, data);
            
    data = SRC_receive(SRC_register_portA_1);
    data |= 1 << 3;    //set SRC as Master
    SRC_send(SRC_register_portA_1, data);
    
    data = 0x00; // Register 0D: Receiver Control Register 1
    SRC_send(SRC_receiver_control_register_1, data);
    
    data = 0x00; // Register 0E: Receiver Control Register 2
    SRC_send(SRC_receiver_control_register_2, data);
    
 
    data = SRC_receive(SRC_register_control_1);
  
    data &= ~(1 << 0);     //set SRC input source to DIR
    data |= 1 << 1;   
    SRC_send(SRC_register_control_1, data);
    
    // PLL1 configuration
    // (input) RXCKI = 16,9344
    // P = 1, J = 5, D = 8050
    SRC_send(SRC_receiver_PLL1_config_1, 0x11);
    SRC_send(SRC_receiver_PLL1_config_2, 0x5F);
    SRC_send(SRC_receiver_PLL1_config_3, 0x72);
    
}

void SRC_set_reset(uint8_t enable){
    uint8_t data = SRC_receive(SRC_register_power);
    
    if (enable == 1) data |= (enable << 7);
    else if (enable == 0) data &= ~(enable << 7);
    
    SRC_send(SRC_register_power, data);  

}

void SRC_set_audio_output_data_format(SRC_audio_output_data_format_t SRC_audio_output_data_format){
    uint8_t data = SRC_receive(SRC_register_portA_1);
    
    switch(SRC_audio_output_data_format){
        case SRC_24_bit_left_justified:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            data &= ~(1 << 2);
            break;
        case SRC_24_bit_I2S:
            data |= 1 << 0;
            data &= ~(1 << 1);
            data &= ~(1 << 2);
            break;
		case SRC_16_bit_right_justified:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            data |= 1 << 2;
            break;
		case SRC_18_bit_right_justified:
            data |= 1 << 0;
            data &= ~(1 << 1);
            data |= 1 << 2;
            break;
		case SRC_20_bit_right_justified:
            data &= ~(1 << 0);
            data |= 1 << 1;
            data |= 1 << 2;
            break;
		case SRC_24_bit_right_justified:
            data |= 1 << 0;
            data |= 1 << 1;
            data |= 1 << 2;
            break;
    }
    
    SRC_send(SRC_register_portA_1, data);    
}

SRC_audio_output_data_format_t SRC_get_audio_data_format(void){
    uint8_t data = SRC_receive(SRC_register_portA_1);
    return (data & SRC_AUDIO_FORMAT);
}

void SRC_set_master_clock_divider(SRC_master_clock_divider_t SRC_master_clock_divider){
    uint8_t data = SRC_receive(SRC_register_portA_2);

    switch(SRC_master_clock_divider){
        case SRC_Divide128:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            break;
        case SRC_Divide256:
            data |= 1 << 0;
            data &= ~(1 << 1);
            break;
		case SRC_Divide384:
            data &= ~(1 << 0);
            data |= 1 << 1;
            break;
		case SRC_Divide512:
            data |= 1 << 0;
            data |= 1 << 1;
            break;
    }
    SRC_send(SRC_register_portA_2, data); 
}

SRC_master_clock_divider_t SRC_get_master_clock_divider(void){
    uint8_t data = SRC_receive(SRC_register_portA_2);
    return (data & SRC_MASTER_CLK_DIV);

}

void SRC_set_master_clock_source(SRC_master_clock_sources_t SRC_master_clock_sources){
    uint8_t data = SRC_receive(SRC_register_portA_2);

    switch(SRC_master_clock_sources){
        case SRC_MCLK:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            break;
        case SRC_RXCKI:
            data |= 1 << 0;
            data &= ~(1 << 1);
            break;
    }
    SRC_send(SRC_register_portA_2, data); 
}

SRC_master_clock_sources_t SRC_get_master_clock_source(void){
    uint8_t data = SRC_receive(SRC_register_portA_2);
    return (data & SRC_MASTER_CLK_SRC);
    
}

void SRC_set_data_source(SRC_data_sources_t SRC_data_sources){
    uint8_t data = SRC_receive(SRC_register_portA_1);

    switch(SRC_data_sources){
        case SRC_DIR:
            data &= ~(1 << 4);
            data |= 1 << 5;
            break;
        case SRC_SRC:
            data |= 1 << 4;
            data |= 1 << 5;
            break;
    }
    SRC_send(SRC_register_portA_1, data); 
}

SRC_data_sources_t SRC_get_data_source(void){
    uint8_t data = SRC_receive(SRC_register_portA_1);
    return (data & SRC_DATA_SOURCE);
}


void SRC_set_output_mute(uint8_t enable){
    uint8_t data = SRC_receive(SRC_register_portA_1);
    
    if (enable == 1) data |= (enable << 6);
    else if (enable == 0) data &= ~(enable << 6);
    
    SRC_send(SRC_register_portA_1, data);   
}

void SRC_set_word_length(SRC_word_length_t SRC_word_length){
    uint8_t data = SRC_receive(SRC_register_control_3);

    switch(SRC_word_length){
        case SRC_WORD_LENGTH24:
            data &= ~(1 << 7);
            data &= ~(1 << 6);
            break;
        case SRC_WORD_LENGTH20:
            data &= ~(1 << 7);
            data |= 1 << 6;
            break;
        case SRC_WORD_LENGTH18:
            data |= 1 << 7;            
            data &= ~(1 << 6);
            break;
        case SRC_WORD_LENGTH16:
            data |= 1 << 7;
            data |= 1 << 6;
            break;            
    }
    SRC_send(SRC_register_control_3, data); 
}

SRC_word_length_t SRC_get_word_length(void){
    uint8_t data = SRC_receive(SRC_register_control_3);
    return (data & SRC_WORD_LENGTH);
}

void SRC_set_page(SRC_page_selection_t SRC_page_selection){
    uint8_t data = SRC_receive(SRC_page_selection_register);

    switch(SRC_page_selection){
        case SRC_PAGE0:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            break;
        case SRC_PAGE1:
            data |= 1 << 0;
            data &= ~(1 << 1);
            break;
        case SRC_PAGE2:
            data &= ~(1 << 0);            
            data |= 1 << 1;            
            break;
        case SRC_PAGE3:
            data |= 1 << 0;
            data |= 1 << 1;
            break;            
    }
    SRC_send(SRC_page_selection_register, data); 
}

SRC_page_selection_t SRC_get_page(void){
    uint8_t data = SRC_receive(SRC_page_selection_register);
    return (data);
}