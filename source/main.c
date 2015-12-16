/**
 * @file    main.c
 *
 * @brief   Main Function of DAC1 Project
 * 
 * This is the main routine of DAC1 Project.
 * 
 * @author  Sebastian Wolfarth
 * @date    29.10.15 - inital version
 * 
 * @version 0.1
 */


#include <xc.h>
#include <stdio.h>

#include "log.h"
#include "UART_API.h"
#include "SPI_API.h"
#include "DEC_API.h"
#include "xlcd/xlcd.h"
#include "PCM_API.h"

#include <libpic30.h>

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = LPRCDIVN         // Oscillator Mode (Internal Fast RC (FRC) with divide by N)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog timer always enabled)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

int main(void) {
    AD1PCFGL = 0x1fff;
    state_rotation_t dec_test = DEC_NO_TURN;

    //=======================================
    // initalisation of the modules
    log_init();
    LOG("\n\nLOG: main()\n");
    LOG("LOG: xlcd_init()\n");
    xlcd_init();
    LOG("LOG: spi_init()\n");
    spi_init();
    LOG("LOG: DEC_init()\n");
    DEC_init();
    
    LOG("\n=================\n\n");
    
    LOG("LOG: PCM_set_soft_mute: %i\n",PCM_enabled);
    PCM_set_soft_mute(PCM_enabled);
    LOG("LOG: PCM_get_soft_mute: %i\n",PCM_get_soft_mute());
    
    LOG("LOG: PCM_set_soft_mute: %i\n",PCM_disabled);
    PCM_set_soft_mute(PCM_disabled);
    LOG("LOG: PCM_get_soft_mute: %i\n",PCM_get_soft_mute());
    
    LOG("\n=================\n\n");
    
    LOG("LOG: PCM_set_audio_data_format: %i\n",PCM_16_bit_standard_format);
    PCM_set_audio_data_format(PCM_16_bit_standard_format);
    LOG("LOG: PCM_get_audio_data_format: %i\n",PCM_get_audio_data_format());
    
    LOG("LOG: PCM_set_audio_data_format: %i\n",PCM_20_bit_standard_format);
    PCM_set_audio_data_format(PCM_20_bit_standard_format);
    LOG("LOG: PCM_get_audio_data_format: %i\n",PCM_get_audio_data_format());
    
    LOG("LOG: PCM_set_audio_data_format: %i\n",PCM_24_bit_standard_format);
    PCM_set_audio_data_format(PCM_24_bit_standard_format);
    LOG("LOG: PCM_get_audio_data_format: %i\n",PCM_get_audio_data_format());
    
    LOG("LOG: PCM_set_audio_data_format: %i\n",PCM_24_bit_MSB_first);
    PCM_set_audio_data_format(PCM_24_bit_MSB_first);
    LOG("LOG: PCM_get_audio_data_format: %i\n",PCM_get_audio_data_format());
    
    LOG("LOG: PCM_set_audio_data_format: %i\n",PCM_16_bit_I2S);
    PCM_set_audio_data_format(PCM_16_bit_I2S);
    LOG("LOG: PCM_get_audio_data_format: %i\n",PCM_get_audio_data_format());
    
    LOG("LOG: PCM_set_audio_data_format: %i\n",PCM_24_bit_I2S);
    PCM_set_audio_data_format(PCM_24_bit_I2S);
    LOG("LOG: PCM_get_audio_data_format: %i\n",PCM_get_audio_data_format());
    
    LOG("\n=================\n\n");
    
    LOG("LOG: PCM_set_oversampling_rate: %i\n",PCM_64_times_fs);
    PCM_set_oversampling_rate(PCM_64_times_fs);
    LOG("LOG: PCM_get_oversampling_rate: %i\n",PCM_get_oversampling_rate());
    
    LOG("LOG: PCM_set_oversampling_rate: %i\n",PCM_32_times_fs);
    PCM_set_oversampling_rate(PCM_32_times_fs);
    LOG("LOG: PCM_get_oversampling_rate: %i\n",PCM_get_oversampling_rate());
    
    LOG("LOG: PCM_set_oversampling_rate: %i\n",PCM_128_times_fs);
    PCM_set_oversampling_rate(PCM_128_times_fs);
    LOG("LOG: PCM_get_oversampling_rate: %i\n",PCM_get_oversampling_rate());
    
    LOG("\n=================\n\n");
    
    LOG("LOG: PCM_set_zero_detect_mute: %i\n",PCM_enabled);
    PCM_set_zero_detect_mute(PCM_enabled);
    LOG("LOG: PCM_get_zero_detect_mute: %i\n",PCM_get_zero_detect_mute());
    
    LOG("LOG: PCM_set_zero_detect_mute: %i\n",PCM_disabled);
    PCM_set_zero_detect_mute(PCM_disabled);
    LOG("LOG: PCM_get_zero_detect_mute: %i\n",PCM_get_zero_detect_mute());
    
    LOG("\n=================\n\n");
    
    LOG("LOG: PCM_set_monaural_mode: %i\n",PCM_mono);
    PCM_set_monaural_mode(PCM_mono);
    LOG("LOG: PCM_get_monaural_mode: %i\n",PCM_get_monaural_mode());
    
    LOG("LOG: PCM_set_monaural_mode: %i\n",PCM_stereo);
    PCM_set_monaural_mode(PCM_stereo);
    LOG("LOG: PCM_get_monaural_mode: %i\n",PCM_get_monaural_mode());
    
    LOG("\n=================\n\n");
    
    LOG("LOG: PCM_set_data_channel: %i\n",PCM_left_channel);
    PCM_set_data_channel(PCM_left_channel);
    LOG("LOG: PCM_get_data_channel: %i\n",PCM_get_data_channel());
    
    LOG("LOG: PCM_set_data_channel: %i\n",PCM_right_channel);
    PCM_set_data_channel(PCM_right_channel);
    LOG("LOG: PCM_get_data_channel: %i\n",PCM_get_data_channel());
    
    LOG("\n=================\n\n");
    
    LOG("LOG: PCM_get_left_zero_detection: %i\n",PCM_get_left_zero_detection());
    LOG("LOG: PCM_get_rigth_zero_detection: %i\n",PCM_get_rigth_zero_detection());
    
    while(1){
    	dec_test = get_DEC_status();
    	switch (dec_test){
            case DEC_TURN_LEFT:
                LOG("L\n");
                break;
            case DEC_TURN_RIGHT:
                LOG("R\n");
                break;
            case DEC_BUTTON:
                LOG("B\n");
                break;
    	}
    }

    while(1); 
}
