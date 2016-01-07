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

#define REPEAT_Q_READ   1000


void SRC_send (uint8_t address, uint8_t data){
    uint8_t data_send[3] = {address, 0, data};
    uint8_t data_receive[3] = {0, 0, 0};
    
    //SRC_LOG("SRC send: Register: 0x%x || Data: 0x%x\n", address, *(data_send + 2));
    spi_rw_n(data_send, data_receive, 3, SPI_SRC_channel);
}

 uint8_t SRC_receive (uint8_t address){
    address |= (1 << 7);    //maybe global define address_read_bit for src and pcm
    uint8_t data_send[3] = {address, 0, 0};
    uint8_t data_receive[3] = {0, 0, 0};
    
    spi_rw_n(data_send, data_receive, 3, SPI_SRC_channel);
    //SRC_LOG("SRC rece: Register: 0x%x || Data: 0x%x\n", address, *(data_receive + 2));
    
    return *(data_receive + 2);
 }

void SRC_init (void){
    SRC_set_output_mute(0); // SRC has no mute functionality
    SRC_set_master_clock_source(SRC_MCLK);
    SRC_set_data_source(SRC_SRC);
    
    uint16_t data = 0x3F; // enable all fuction blocks on SRC
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
    
    data = 0x33;    
    SRC_send(SRC_receiver_interrupt_mask, data); //set interrupts aktiv 
    
    data = 0x00;
    SRC_send(SRC_src_dit_interrupt_mode, data);
    
    data = 0xFF;
    SRC_send(SRC_receiver_interrupt_mask, data); //set interrupts aktiv 
    
    data = 0x01;
    SRC_send(SRC_receiver_interrupt_mask2, data); //set interrupts aktiv 
    
    data = 0x00;
    SRC_send(SRC_receiver_interrupt_mode, data);
    
    data = 0x00;
    SRC_send(SRC_receiver_interrupt_mode2, data);
    
    data = 0x00;
    SRC_send(SRC_receiver_interrupt_mode3, data);
    
    LOG("\n= SRC PLL=\n");
    // PLL1 configuration
    // (input) RXCKI = 16,9344
    // P = 1, J = 5, D = 8050
    SRC_send(SRC_receiver_PLL1_config_1, 0x11);
    SRC_send(SRC_receiver_PLL1_config_2, 0x5F);
    SRC_send(SRC_receiver_PLL1_config_3, 0x72);

    
}

void SRC_set_reset(uint16_t enable){
    uint16_t data = SRC_receive(SRC_register_power);
    
    if (enable == 1) data |= (1 << 7);
    else if (enable == 0) data &= ~(1 << 7);
    
    SRC_send(SRC_register_power, data);  

}

void SRC_set_audio_output_data_format(SRC_audio_output_data_format_t SRC_audio_output_data_format){
    uint16_t data = SRC_receive(SRC_register_portA_1);
    
    switch(SRC_audio_output_data_format){
        case SRC_24_bit_left_justified:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            data &= ~(1 << 2);
            break;
        case SRC_24_bit_I2S:
            data |= (1 << 0);
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

SRC_audio_output_data_format_t SRC_get_audio_output_data_format(void)
{
    uint16_t data = (SRC_receive(SRC_register_portA_1) & SRC_AUDIO_FORMAT);
    
    switch(data)
    {
        case 0: return SRC_24_bit_left_justified;
        case 1: return SRC_24_bit_I2S;
        case 2:
        case 3:
            SRC_LOG("SRC: SRC_get_audio_output_data_format() unsupported format");
            return 0;
        case 4: return SRC_16_bit_right_justified;
        case 5: return SRC_18_bit_right_justified;
        case 6: return SRC_20_bit_right_justified;
        case 7: return SRC_24_bit_right_justified;
    }
    
    return 0;
}

void SRC_set_master_clock_divider(SRC_master_clock_divider_t SRC_master_clock_divider){
    uint16_t data = SRC_receive(SRC_register_portA_2);

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
    uint16_t data = SRC_receive(SRC_register_portA_2);
    return (data & SRC_MASTER_CLK_DIV);

}

void SRC_set_master_clock_source(SRC_master_clock_sources_t SRC_master_clock_sources){
    uint16_t data = SRC_receive(SRC_register_portA_2);

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
    uint16_t data = SRC_receive(SRC_register_portA_2);
    return ((data & SRC_MASTER_CLK_SRC)>>2);
    
}

void SRC_set_data_source(SRC_data_sources_t SRC_data_sources){
    uint16_t data = SRC_receive(SRC_register_portA_1);

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
    uint16_t data = SRC_receive(SRC_register_portA_1);
    data = (data & SRC_DATA_SOURCE)>>4;
    
    switch(data)
    {
        case 0:
           // PORT A
            data = 0;
           break;
        case 1:
            data = 0;
            break;
        case 2:
            // DIR (SPDIF Input)
            data = SRC_DIR;
            break;
        case 3:
            // SRC
            data = SRC_SRC;
            break;
    }
    return data;
}


void SRC_set_output_mute(uint16_t enable){
    uint16_t data = SRC_receive(SRC_register_portA_1);
    
    if (enable == 1) data |= (1 << 6);
    else if (enable == 0) data &= ~(1 << 6);
    
    SRC_send(SRC_register_portA_1, data);   
}

uint16_t SRC_get_output_mute(void){
    uint16_t data = SRC_receive(SRC_register_portA_1);
    return (data & SRC_MUTE) >> 6;
}

void SRC_set_word_length(SRC_word_length_t SRC_word_length){
    uint16_t data = SRC_receive(SRC_register_control_3);

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
    uint16_t data = SRC_receive(SRC_register_control_3);
    return (data & SRC_WORD_LENGTH) >> 6;
}

void SRC_set_page(SRC_page_selection_t SRC_page_selection){
    uint16_t data = SRC_receive(SRC_page_selection_register);

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
    uint16_t data = SRC_receive(SRC_page_selection_register);
    return (data);
}

uint16_t SRC_get_receiver_status1(void){
    uint16_t data = SRC_receive(SRC_receiver_status_control1);
    return (data);
}
        

uint16_t SRC_get_receiver_status2(void){
    uint16_t data = SRC_receive(SRC_receiver_status_control2);
    return (data);
}

uint16_t SRC_get_receiver_status3(void){
    uint16_t data = SRC_receive(SRC_receiver_status_control3);
    return (data);
}

uint16_t SRC_get_qchannel_register1(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_1);
    return (data);
}

uint16_t SRC_get_qchannel_register2(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_2);
    return (data);
}

uint16_t SRC_get_qchannel_register3(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_3);
    return (data);
}

uint16_t SRC_get_qchannel_register4(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_4);
    return (data);
}

uint16_t SRC_get_qchannel_register5(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_5);
    return (data);
}

uint16_t SRC_get_qchannel_register6(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_6);
    return (data);
}

uint16_t SRC_get_qchannel_register7(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_7);
    return (data);
}

uint16_t SRC_get_qchannel_register8(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_8);
    return (data);
}

uint16_t SRC_get_qchannel_register9(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_9);
    return (data);
}

uint16_t SRC_get_qchannel_register10(void){
    uint16_t data = SRC_receive(SRC_qchannel_register_10);
    return (data);
}

void SRC_get_play_time(uint16_t* minutes, uint16_t* seconds, uint16_t* aminutes, uint16_t* aseconds){
    uint16_t temp =  SRC_get_qchannel_register4();
    *minutes =  (temp& 0x0F) + ((temp>>4)& 0x0F)*10;
    temp =  SRC_get_qchannel_register5();
    *seconds =  (temp& 0x0F) + ((temp>>4)& 0x0F)*10;
    temp =  SRC_get_qchannel_register8();
    *aminutes =  (temp& 0x0F) + ((temp>>4)& 0x0F)*10;
    temp =  SRC_get_qchannel_register9();
    *aseconds =  (temp& 0x0F) + ((temp>>4)& 0x0F)*10;
    
}

void SRC_get_cd_info(uint16_t* address, uint16_t* track, uint16_t* index){
    uint16_t temp = SRC_get_qchannel_register1();
    *address =  (temp& 0x0F) + ((temp>>4)& 0x0F)*10;
    temp = SRC_get_qchannel_register2();
    *track =  (temp& 0x0F) + ((temp>>4)& 0x0F)*10;
    temp = SRC_get_qchannel_register3();
    *index = (temp& 0x0F) + ((temp>>4)& 0x0F)*10;
}

uint16_t SRC_get_interrupt_status(void){
    uint16_t data = SRC_receive(SRC_interrupt_status);
    return (data);
}

uint16_t SRC_get_src_dit_status(void){
    uint16_t data = SRC_receive(SRC_src_dit_status_register);
    return (data);
}

void SRC_set_mute_pll_error(uint16_t enable){
    uint16_t data = SRC_receive(SRC_receiver_control_register_2);
    
    if (enable == 1) data |= (1 << 3);
    else if (enable == 0) data &= ~(1 << 3);
    
    SRC_send(SRC_receiver_control_register_2, data);  
}

uint16_t SRC_get_mute_pll_error(void){
    uint16_t data = SRC_receive(SRC_receiver_control_register_2);
    return (data & SRC_PLLLOCKERROR) >> 3;   
}

uint16_t SRC_get_non_pcm_audio_detection(void){
    uint16_t data = SRC_receive(SRC_non_pcm_audio_detection_register);
    return (data);
}

void SRC_set_interpolation_filter(SRC_interpolation_filter_t SRC_interpolation_filter){
    uint16_t data = SRC_receive(SRC_register_control_2);

    switch(SRC_interpolation_filter){
        case SRC_INTERPOLATION_FILTER64:
            data &= ~(1 << 0);
            data &= ~(1 << 1);
            break;
        case SRC_INTERPOLATION_FILTER32:
            data |= 1 << 0;
            data &= ~(1 << 1);
            break;
        case SRC_INTERPOLATION_FILTER16:
            data &= ~(1 << 0);            
            data |= 1 << 1;            
            break;
        case SRC_INTERPOLATION_FILTER8:
            data |= 1 << 0;
            data |= 1 << 1;
            break;            
    }
    SRC_send(SRC_register_control_2, data);     
}

SRC_interpolation_filter_t SRC_get_interpolation_filter(void){
    uint16_t data = SRC_receive(SRC_register_control_2);
    return (data & SRC_INTERPOLATION_FILTER);   
}

void SRC_set_automatic_deemphasis(uint16_t enable){
    uint16_t data = SRC_receive(SRC_register_control_2);
    
    if (enable == 1) data |= (1 << 5);
    else if (enable == 0) data &= ~(1 << 5);
    
    SRC_send(SRC_register_control_2, data);  
}

uint16_t SRC_get_automatic_deemphasis(void){
    uint16_t data = SRC_receive(SRC_register_control_2);
    return (data & SRC_DEEMPHASIS) >> 5;   
}

void SRC_set_decimation_filter(SRC_decimation_filter_t SRC_decimation_filter){
    uint16_t data = SRC_receive(SRC_register_control_2);

    switch(SRC_decimation_filter){
        case SRC_DECIMATION_FILTER:
            data &= ~(1 << 0);
            break;
        case SRC_DIRECT_DOWN_SAMPLING:
            data |= 1 << 0;
            break;       
    }
    SRC_send(SRC_register_control_2, data);     
}

SRC_decimation_filter_t SRC_get_decimation_filter(void){
    uint16_t data = SRC_receive(SRC_register_control_2);
    return (data & SRC_DECIMATION) >> 2;   
}

uint16_t SRC_get_minutes(void){
    uint16_t temp;
    uint16_t status;
    int i;
    
    for (i = 0; i < REPEAT_Q_READ; i++){
        // check validty bit
        status = SRC_get_receiver_status2();
        temp =  SRC_get_qchannel_register4();
        //if (((temp & 0x02) >> 1) == 0)
        if(status == 0x08)
        {  
            // bcd conversion
            
            //SRC_LOG("SRC: Track: %i\n", i);
            return  ((temp& 0x0F) + ((temp>>4)& 0x0F)*10);
        }
        
    }
    SRC_LOG("SRC: invalid minutes\n");
    return 0;
}

uint16_t SRC_get_seconds(void){
    uint16_t temp = SRC_get_receiver_status2();
    int i;
    
    for (i = 0; i < REPEAT_Q_READ; i++){
        // check validty bit
        temp = SRC_get_receiver_status2();
        //if (((temp & 0x02) >> 1) == 0)
        if(temp == 0x08)
        {  
            // bcd conversion
            temp =  SRC_get_qchannel_register5();
            //SRC_LOG("SRC: Track: %i\n", i);
            return  ((temp& 0x0F) + ((temp>>4)& 0x0F)*10);
        }
        
    }
    
    SRC_LOG("SRC: invalid seconds\n");
    return 0;    
}

uint16_t SRC_get_track(void){
    int i;
    uint16_t temp;// = SRC_get_receiver_status2();
    
//    do{
//        temp = SRC_get_receiver_status2();
//        
//    }while(temp == 0x09);
     
//    temp =  SRC_get_qchannel_register2();
//    return  ((temp& 0x0F) + ((temp>>4)& 0x0F)*10);
    
    
    for (i = 0; i < REPEAT_Q_READ; i++){
        // check validty bit
        temp = SRC_get_receiver_status2();
        //if (((temp & 0x02) >> 1) == 0)
        if(temp == 0x08)
        {  
            // bcd conversion
            temp =  SRC_get_qchannel_register2();
            //SRC_LOG("SRC: Track: %i\n", i);
            return  ((temp& 0x0F) + ((temp>>4)& 0x0F)*10);
        }
        
    }
    
    SRC_LOG("SRC: invalid track\n");
    return 0;  
}

uint16_t SRC_get_burst_preamble_pc_highbyte(void){
    uint16_t data = SRC_receive(SRC_burst_preamble_pc_highbyte);
    return (data);
}

uint16_t SRC_get_burst_preamble_pc_lowbyte(void){
    uint16_t data = SRC_receive(SRC_burst_preamble_pc_lowbyte);
    return (data);
}