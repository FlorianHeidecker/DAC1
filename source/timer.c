/** 
 * @file        timer.c
 *
 * @brief       simple module to control a timer
 * 
 * @author      Florian Heidecker
 * @date        13.11.2015 - initial version
 * @date        07.12.2015 - rework/comments
 * 
 * @version     0.1
 * 
 */

#include <xc.h>
#include <time.h>

#include "timer.h"
#include "log.h"

 #define _ISR_PSV __attribute__((interrupt, auto_psv))

volatile interrrupt_state_t timer_interrrupt_state;

/**
 * @brief timer initialization
 */
void timer_init(void){
    timer_interrrupt_state = interrupt_no;
    
    T1CONbits.TON = 0;          // disable timer
	
	T1CONbits.TCS = 0;          // select internal instruction cycle clock 
	T1CONbits.TGATE = 0;        // disable gated timer mode
    // FCY = 3,685MHz
    // FCY/64 = 57,578kHz
    // 500ms/(1/57,578kHz) = 28789
	T1CONbits.TCKPS = 0b10;     // select 1:64 prescaler
	TMR1 = 0x00;                // clear timer register
	PR1 = 0x7075;               // load the period value
	
	IPC0bits.T1IP = 0x01;		// set timer1 interrupt priority level
	IFS0bits.T1IF = 0;			// clear timer1 interrupt flag
	IEC0bits.T1IE = 1;			// enable timer1 interrupt
}

/**
 * @brief timer and interrupt started
 */
void timer_start(void){
    TMR1 = 0x00;                // clear timer register
    T1CONbits.TON = 1;          // disable timer
}

/**
 * @brief timer and interrupt stopped
 */
void timer_stop(void){
    T1CONbits.TON = 0;          // disable timer
    TMR1 = 0x00;                // clear timer register
}

void _ISR_PSV _T1Interrupt(void){
    //LOG("T\n");
	TMR1 = 0x00;                        // clear timer register
    timer_interrrupt_state = interrupt_yes;   // set interrupt state
	IFS0bits.T1IF = 0;                  // clear interrupt flag
}