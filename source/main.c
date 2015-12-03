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
#include "xlcd/xlcd.h"
#include "UART_API.h"
#include "menu.h"

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
    log_init();
    
    LOG("\n\nmain()\n");

    
    //=======================================
    // initalisation of the modules
    xlcd_init();
    pll_init();
    menu_init();
    
    menu_call_next();
    LOG("\n");
    menu_call_next();
    LOG("\n");
    menu_call_next();
    LOG("\n");
    menu_call_next();
    LOG("\n");
    menu_call_next();
    LOG("\n");
    menu_call_next();
    LOG("\n");
    menu_call_next();
    LOG("\n");
    menu_call_next();
    LOG("\n");
    
    
    
    //menu_write_line(0);
    
    while(1)
    {
        menu_up();
        asm("nop");
    }
    
    



    while(1); 
}