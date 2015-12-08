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
#include "SPI_API.h"
#include "DEC_API.h"
#include "xlcd/xlcd.h"

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
    char dec_record[10];
    uint16_t record_pos = 0x00;
    state_rotation_t dec_test = DEC_NO_TURN;

    //=======================================
    // initalisation of the modules
    log_init();
    LOG("\n\nLOG: main()\n");
    
    LOG("LOG: xlcd_init()\n");
    xlcd_init();
    LOG("LOG: pll_init()\n");
    pll_init();
    LOG("LOG: spi_init()\n");
    spi_init();
    LOG("LOG: DEC_init()\n");
    DEC_init();
    
    while(1){
    	dec_test = get_DEC_status();
    	switch (dec_test){
            case DEC_TURN_LEFT:     dec_record[record_pos]='L';
                                    record_pos++;
                                    LOG("L\n");
                                    break;
            case DEC_TURN_RIGHT:    dec_record[record_pos]='R';
                                    record_pos++;
                                    LOG("R\n");
                                    break;
            case DEC_BUTTON:        dec_record[record_pos]='B';
                                    record_pos++;
                                    LOG("B\n");
                                    break;
            default:                break;
    	}
//    	if(record_pos == 0x09){
//        	for(record_pos=0x00;record_pos<0x0A;record_pos++){
//            		LOG("%c\n",dec_record[record_pos]);
//        	}
//            for(record_pos=0x00;record_pos<0x0A;record_pos++){
//            		dec_record[record_pos]=0x00;
//        	}
//            
//        	
//    	}
        record_pos = 0x00;
        
    }



    while(1); 
}