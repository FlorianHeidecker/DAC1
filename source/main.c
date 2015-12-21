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
#include "PLL_API.h"
#include "UART_API.h"
#include "menu.h"

#include <libpic30.h>
#include "SPI_API.h"
#include "DEC_API.h"
#include "xlcd/xlcd.h"
#include "SRC_API.h"
#include "PCM_API.h"
#include "PLL_API.h"

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
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (Watchdog timer always enabled)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

int main(void) {
    AD1PCFGL = 0x1fff;
    state_rotation_t dec_test = DEC_NO_TURN;
    uint16_t minutes, seconds, aminutes, aseconds ,address, track, index, receiver_status2, preamble_high, preamble_low, pcmAudioDec =0x00;
    
    //=======================================
    // initalisation of the modules
    log_init();
    LOG("\n\nLOG: main()\n");

    LOG("LOG: xlcd_init()\n");
    xlcd_init();
    LOG("LOG: pll_init()\n");
    PLL_init();
    LOG("LOG: menu_init()\n");
    menu_init();
    LOG("LOG: spi_init()\n");
    spi_init();
    LOG("LOG: DEC_init()\n");
    DEC_init();
        
    PLL_init();
    LOG("LOG: PLL_init()\n");
            
    SRC_init();
    SRC_set_audio_output_data_format(SRC_24_bit_I2S);
    SRC_set_output_mute(0);
    SRC_set_master_clock_source(SRC_MCLK);
    SRC_set_master_clock_divider(SRC_Divide128);
    SRC_set_data_source(SRC_SRC);
    SRC_set_word_length(SRC_WORD_LENGTH24);  
    
    
    while(1){
    	dec_test = get_DEC_status();
    	switch (dec_test)
        {
            case DEC_TURN_LEFT:     
                LOG("L\n");
                menu_btn_down();
                SRC_get_cd_info(&address, &track, &index);
                LOG("Add=%i,Tra=%i,Ind=%i\n",address, track, index);
                SRC_get_play_time( &minutes, &seconds, &aminutes, &aseconds);
                LOG("M=%i,S=%i,aM=%i,aS=%i\n",minutes, seconds, aminutes, aseconds);
                receiver_status2 = SRC_get_receiver_status2();
                LOG("ReStat2_0b=%b\n",receiver_status2);
                preamble_high = SRC_get_burst_preamble_pc_highbyte();
                LOG("PreambleHigh_0b=%b\n",preamble_high);
                preamble_low = SRC_get_burst_preamble_pc_lowbyte();
                LOG("PreambleLow_0b=%b\n",preamble_low);
                pcmAudioDec =SRC_get_non_pcm_audio_detection();
                LOG("NonPCMAuDec_0b=%b\n",pcmAudioDec);
                break;
                
            case DEC_TURN_RIGHT:    
                LOG("R\n");
                menu_btn_up();
                break;
            
            case DEC_BUTTON:        
                LOG("B\n");
                menu_btn_set();
                break;
                
            default:
                break;
    	}
    }

    while(1); 
}
