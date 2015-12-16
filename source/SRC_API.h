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
 
#ifndef _SRC_API_H
#define _SRC_API_H

#include <xc.h>

//== typedefs ==================================================================

#define SRC_AUDIO_FORMAT 0x07
#define SRC_MASTER_CLK_DIV 0x03
#define SRC_DATA_SOURCE 0x30
#define SRC_MASTER_CLK_SRC 0x0C
#define SRC_WORD_LENGTH 0xC0
#define SRC_INTERPOLATION_FILTER 0x03
#define SRC_DECIMATION 0x04

/** SRC: possible audio output data format selection */
typedef enum {	SRC_24_bit_left_justified=0,
				SRC_24_bit_I2S=1,
                SRC_16_bit_right_justified = 4,
				SRC_18_bit_right_justified = 5,
                SRC_20_bit_right_justified = 6,
				SRC_24_bit_right_justified = 7} SRC_audio_output_data_format_t;
 
/** SRC: possible clock sources selection */               
typedef enum {	SRC_MCLK=0,
				SRC_RXCKI=1 } SRC_master_clock_sources_t;    
                
/** SRC: possible data sources port a */               
typedef enum {	SRC_DIR=2,
				SRC_SRC=3 } SRC_data_sources_t;                  
                
/** SRC: possible clock sources divider */               
typedef enum {	SRC_Divide128 = 0,
				SRC_Divide256 = 1,
                SRC_Divide384 = 2,
                SRC_Divide512 = 3} SRC_master_clock_divider_t;    
                
/** SRC: possible output word length */               
typedef enum {	SRC_WORD_LENGTH24 = 0,
				SRC_WORD_LENGTH20 = 1,
                SRC_WORD_LENGTH18 = 2,
                SRC_WORD_LENGTH16 = 3} SRC_word_length_t;  
                
/** SRC: Page selection */               
typedef enum {	SRC_PAGE0 = 0,
				SRC_PAGE1 = 1,
                SRC_PAGE2 = 2,
                SRC_PAGE3 = 3} SRC_page_selection_t; 
                
/** SRC: Interpolation Filter */               
typedef enum {	SRC_INTERPOLATION_FILTER64 = 0,
				SRC_INTERPOLATION_FILTER32 = 1,
                SRC_INTERPOLATION_FILTER16 = 2,
                SRC_INTERPOLATION_FILTER8 =  3} SRC_interpolation_filter_t; 
                
/** SRC: Decimation Filter/Direct Down Sampling */               
typedef enum {	SRC_DECIMATION_FILTER = 0,
				SRC_DIRECT_DOWN_SAMPLING = 1 } SRC_decimation_filter_t;                 

          
/** SRC: available register */
typedef enum {	SRC_register_power = 0x01,
                SRC_interrupt_status = 0x02,
                SRC_register_portA_1 = 0x03,   
                SRC_register_portA_2 = 0x04,
                SRC_receiver_control_register_1 = 0x0D,
                SRC_receiver_control_register_2 = 0x0E,
                SRC_receiver_PLL1_config_1 = 0x0F,
                SRC_receiver_PLL1_config_2 = 0x10,
                SRC_receiver_PLL1_config_3 = 0x11,
                SRC_qchannel_register_1 = 0x1F,
                SRC_qchannel_register_2 = 0x20,
                SRC_qchannel_register_3 = 0x21,
                SRC_qchannel_register_4 = 0x22,
                SRC_qchannel_register_5 = 0x23,
                SRC_qchannel_register_6 = 0x24,
                SRC_qchannel_register_7 = 0x25,
                SRC_qchannel_register_8 = 0x26,
                SRC_qchannel_register_9 = 0x27,
                SRC_qchannel_register_10 = 0x28,        
                SRC_register_control_1 = 0x2D,
                SRC_register_control_2 = 0x2E,
                SRC_register_control_3 = 0x2F,
                SRC_page_selection_register = 0x7F,
                SRC_non_pcm_audio_detection_register = 0x12,
                SRC_receiver_status_control1 = 0x13,  
                SRC_receiver_status_control2 = 0x14,
                SRC_receiver_status_control3 = 0x15,
                SRC_src_dit_status_register = 0x0A  } SRC_register_t;                
                

//== functions =================================================================

                
/*
 * @brief           send function for src
 * 
 * @param address   register to write 
 * @param data      write data
 * 
 */
                
 void SRC_send (uint8_t address, uint8_t data);    
 
 /*
 * @brief           receive function for src
 * 
 * @param address   register to read 
 * @return          requested data
 * 
 */
 uint8_t SRC_receive (uint8_t address);   
                                                  
/*
 * @brief   set some init params, e.g. I2SMaster
 *
 */
void SRC_init (void);

/*
 * @brief   bit is used to force a reset initialization sequence, and is equivalent to forcing an external
 *          reset via the RST input 
 *                  
 * 
 * @param enable:     
 *                   0 Disabled (Default)
 *                   1 Enabled; all control registers will be reset to the default state.
 */
void SRC_set_reset(uint8_t enable);

/**
 * @brief           set audio interface data format
 * 
 * @param SRC_audio_output_data_format     see
 *                                         SRC: possible audio data format selection
 *                                         -> SRC_audio_data_format_t
 */
void SRC_set_audio_output_data_format(SRC_audio_output_data_format_t SRC_audio_output_data_format);

/**
 * @brief           get audio interface data format
 * 
 * @return          see
 *                  : possible audio data format selection
 *                  -> SRC_audio_data_format_t
 */
SRC_audio_output_data_format_t SRC_get_audio_output_data_format(void);

/*
 * @brief           set divider for master clock port a
 *                  
 * 
 * @param SRC_master_clock_divider     see
 *                                     SRC: possible master clock sources
 *                                     -> SRC_master_clock_divider_t
 */
void SRC_set_master_clock_divider(SRC_master_clock_divider_t SRC_master_clock_divider);

/**
 * @brief           get divider for master clock port a
 * 
 * @return          see
 *                  SRC: possible master clock sources
 *                  -> SRC_master_clock_divider_t
 */
SRC_master_clock_divider_t SRC_get_master_clock_divider(void);

/*
 * @brief           set source for master clock port a
 *                  
 * 
 * @param SRC_master_clock_sources      see
 *                                      SRC: possible master clock sources
 *                                      -> SRC_master_clock_sources_t
 */
void SRC_set_master_clock_source(SRC_master_clock_sources_t SRC_master_clock_sources);

/**
 * @brief           get source for master clock port a
 * 
 * @return          see
 *                  SRC: possible master clock sources
 *                  -> SRC_master_clock_sources_t
 */
SRC_master_clock_sources_t SRC_get_master_clock_source(void);

/*
 * @brief           set data source for port a
 *                  
 * 
 * @param SRC_data_sources_             see
 *                                      SRC: possible data sources
 *                                      -> SRC_porta_data_sources_t
 */
void SRC_set_data_source(SRC_data_sources_t SRC_data_sources);

/**
 * @brief           get data source for port a
 * 
 * @return          see
 *                  SRC: possible master clock sources
 *                  -> SRC_master_clock_sources_t
 */
SRC_data_sources_t SRC_get_data_source(void);


/*
 * @brief   This bit is used to mute the Port A audio data output. 
 *                  
 * 
 * @param enable:     
 *                0 Disabled; SDOUTA is driven by the output data source. (Default)
 *                1 Enabled; SDOUTA is forced low.
 */
void SRC_set_output_mute(uint8_t enable);

/*
 * @brief           set output word length
 *                  
 * 
 * @param SRC_word_length             see
 *                                      SRC: possible output word length
 *                                      -> SRC_word_length_t
 */
void SRC_set_word_length(SRC_word_length_t SRC_word_length);

/**
 * @brief           get output word length
 * 
 * @return          see
 *                  SRC: possible output word length
 *                  -> SRC_word_length_t
 */
SRC_word_length_t SRC_get_word_length(void);

/*
 * @brief           These bits are utilized to select one of three register pages for write and/or read. 
 *                  The Page Selection Register is present on every register page at
 *                  address 0x7F, allowing movement between pages as necessary.
 *                  
 * 
 * @param SRC_page_slection           see
 *                                    SRC: set page 
 *                                    -> SRC_page_selection_t
 */
void SRC_set_page(SRC_page_selection_t SRC_page_selection);

/**
 * @brief           get the current page
 * 
 * @return          see
 *                  SRC: get page
 *                  -> SRC_page_selection_t
 */
SRC_page_selection_t SRC_get_page(void);

/**
 * @brief           get information of qchannel register 1
 * 
 * @return          infos about control and address
 *                  
 */
uint8_t SRC_get_qchannel_register1(void);


/**
 * @brief           get information of qchannel register 2
 * 
 * @return          infos about track
 *                  
 */
uint8_t SRC_get_qchannel_register2(void);

/**
 * @brief           get information of qchannel register 3
 * 
 * @return          infos about index
 *                  
 */
uint8_t SRC_get_qchannel_register3(void);

/**
 * @brief           get information of qchannel register 4
 * 
 * @return          infos about minutes
 *                  
 */
uint8_t SRC_get_qchannel_register4(void);

/**
 * @brief           get information of qchannel register 5
 * 
 * @return          infos about seconds
 *                  
 */
uint8_t SRC_get_qchannel_register5(void);

/**
 * @brief           get information of qchannel register 6
 * 
 * @return          infos about frame
 *                  
 */
uint8_t SRC_get_qchannel_register6(void);

/**
 * @brief           get information of qchannel register 7
 * 
 * @return          8 bit zeros to differ between register 4-6 and 8-10
 *                  
 */
uint8_t SRC_get_qchannel_register7(void);

/**
 * @brief           get information of qchannel register 8
 * 
 * @return          infos about absolut min
 *                  
 */
uint8_t SRC_get_qchannel_register8(void);

/**
 * @brief           get information of qchannel register 9
 * 
 * @return          infos about absolut sec 
 *                  
 */
uint8_t SRC_get_qchannel_register9(void);

/**
 * @brief           get information of qchannel register 10
 * 
 * @return          infos about absolut frame
 *                  
 */
uint8_t SRC_get_qchannel_register10(void);

/*
 * @brief           get information about play time of the actual titel and the whole time
 *                   
 * @param minutes    played minutes of the actual titel            
 * @param seconds    played seconds of the actual titel  
 * @param aminutes   played minutes of the whole cd                                       
 * @param aseconds   played seconds of the whole cd     
 *                                    
 */
void SRC_get_play_time(uint8_t* minutes, uint8_t* seconds, uint8_t* aminutes, uint8_t* aseconds);

/*
 * @brief           get information about address, track and index
 *                   
 * @param address               
 * @param track     
 * @param index                                           
 *                                    
 */
void SRC_get_cd_info(uint8_t* address, uint8_t* track, uint8_t* index);

/*
 * @brief   These two bits indicate the maximum available RXCKO clock rate based 
 *          upon the DIR detection       
 * 
 * @return  RXCKR1 RXCKR0 Maximum Available RXCKO Rate
 *           0 0 Clock rate not determined.
 *           0 1 128fs
 *           1 0 256fs
 *           1 1 512fs        
 *                  
 *                  
 */
uint8_t SRC_get_receiver_status1(void);

/**
 * @brief  Information about Channel, Parity, Validity, Bipolar, Q-Channel Status       
 * 
 * @return 8 bit code, s. datasheet page 65         
 *                
 *                 
 */
uint8_t SRC_get_receiver_status2(void);

/**
 * @brief   Receiver Output Data Slip Error Status      
 * 
 * @return  
 *              OSLIP Receiver OSLIP Error Status
 *               0 No Error
 *               1 DIR Output Data Slip/Repeat Error Detected        
 *                
 *                 
 */
uint8_t SRC_get_receiver_status3(void);

/**
 * @brief   Global Interrupt Status [2:0]      
 * 
 * @return  
 *          Bit0: SRC Function Block Interrupt Status (Active High) -> read 0x0A     
 *          Bit1: Receiver Function Block Interrupt Status (Active High) -> read 0x14 and 0x15                
 *          Bit2: Transmitter Function Block Interrupt Status (Active High) -> read 0x0A               
 */
uint8_t SRC_get_interrupt_status(void);

/**
 * @brief    SRC and DIT Status, s. page 59    
 * 
 * @return  
 *          Bit0: Transmitter Buffer Transfer Status, Active High
 *          Bit1: Transmitter Source Data Slip Status, Active High             
 *          Bit4: SRC Rate Estimator Ready Status, Active High    
 *          Bit5: SRC Ratio Status, Active High       
 */
uint8_t SRC_get_src_dit_status(void);

/**
 * @brief    This bit is used to set the automatic mute function for the DIR 
 *          block when a loss of lock is indicated by both the AES3 decoder and PLL2.    
 * 
 * @return  
 *              0 Disabled (Default)
 *               1 Enabled; audio data output from the DIR block is forced low for a loss of
 *               lock condition   
 */
void SRC_set_mute_pll_error(uint8_t enable);

/**
 * @brief     Non-PCM Audio Detection Status Register; This bit is utilized to 
 *            indicate the detection of an IEC 61937 data reduced audio format
 *            (includes Dolby AC-3, DTS, etc.) for DVD playback or general transmission purposes.    
 * 
 * @return       Bit0:
 *               0 Data is not an IEC61937 format.
 *               1 Data is an IEC61937 format. Refer to the PC and PD preamble
 *                 registers
 *               Bit1:
 *               0 The CD/LD is not DTS encoded.
 *               1 DTS CD/LD playback detected.
 */
uint8_t SRC_get_non_pcm_audio_detection(void);

/*
 * @brief           set samples of interpolation filter
 *                  
 * 
 * @param number of samples for interpolation  see
 *                                      SRC: SRC_interpolation_filter_t
 *                                      
 */
void SRC_set_interpolation_filter(SRC_interpolation_filter_t SRC_interpolation_filter);

/**
 * @brief           get samples of interpolation filter
 *  
 * @return          64,32,16,8 samples                  
 *                  see
 *                  -> SRC_interpolation_filter_t
 */
SRC_interpolation_filter_t SRC_get_interpolation_filter(void);

/*
 * @brief           This bit enables or disables the automatic de-emphasis function,
 *                  
 * 
 * @param           0 Disabled (Default)
 *                  1 Enabled
 *                                      
 */
void SRC_set_automatic_deemphasis(uint8_t enable);

/*
 * @brief           This bit selects the mode of the decimation function,
 *                  either true decimation filter or direct down-
 *                  sampling without filtering.
 *                  
 * 
 * @param           see
 *                  SRC: SRC_decimation_filter_t
 *                                      
 */
void SRC_set_decimation_filter(SRC_decimation_filter_t SRC_decimation_filter);

/**
 * @brief           get status of filter
 *  
 * @return          see               
 *                  -> SRC_decimation_filter             
 *                  
 */
SRC_decimation_filter_t SRC_get_decimation_filter(void);


#endif /* _SRC_API_H */

