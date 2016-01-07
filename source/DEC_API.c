/** 
 * @file        DEC_API
 *
 * @brief       DEC_API contains the basic functions for the rotary encoder
 *
 * This Module implements the basic functions for the rotary encoder. 
 * The Module contains functions to read the button and get the direction of
 * the rotation whenn the stick is turned left or right. 
 * 
 * @author      Philipp Schenk
 * @date        18.11.2015 - initial version
 * 
 * @version     0.4
 *
 */


#include <xc.h>
#include <stdint.h>
#include "global.h"
#include "DEC_API.h"

#define _IC_NO_PSV __attribute__((interrupt, no_auto_psv))

static state_rotation_t state_rotation = DEC_NO_TURN;
static state_rotation_t button_old = DEC_NO_TURN;

//static state_rotation_t dec_old = DEC_NO_TURN;
//
//void DEC_init(void){
//    AD1PCFGL       |= 0x1800; /*Set AN11, AN12 to Digital Pins*/ 
//    DEC_CHA_TRIS    = 1; /* input */
//    DEC_CHB_TRIS    = 1; /* input */
//    DEC_TASTE_TRIS  = 1; /* input */
//}
//
//unsigned char get_DEC_button(void){
//    if(!DEC_TASTE_PORT && button_old == DEC_NO_TURN){
//        button_old = DEC_BUTTON;
//        return DEC_BUTTON;
//    }
//    else if(DEC_TASTE_PORT && button_old == DEC_BUTTON){
//        button_old = DEC_NO_TURN;
//        return DEC_NO_TURN;
//    }
//    else
//        return DEC_NO_TURN;
//}
//
//state_rotation_t get_DEC_status(void){
//    uint16_t dec_inp = 0x00;
//    
//    if(!DEC_TASTE_PORT && button_old == DEC_NO_TURN){
//        button_old = DEC_BUTTON;
//        return DEC_BUTTON;
//    }
//    else if(DEC_TASTE_PORT && button_old == DEC_BUTTON){
//        button_old = DEC_NO_TURN;
//        return DEC_NO_TURN;
//    }
//    else{
//        dec_inp = (DEC_CHB_PORT <<4) | (DEC_CHA_PORT);
//        if(dec_inp ==0x10 && dec_old == DEC_NO_TURN){
//            dec_old = DEC_TURN_RIGHT;
//            return DEC_NO_TURN;
//        }
//        else if(dec_inp ==0x11 && dec_old == DEC_TURN_RIGHT){
//            dec_old = DEC_NO_TURN;
//            return DEC_TURN_RIGHT;
//        }
//        else if(dec_inp == 0x00 && dec_old == DEC_NO_TURN){
//            dec_old = DEC_TURN_LEFT;
//            return DEC_NO_TURN;
//        }
//        else if(dec_inp ==0x11 && dec_old == DEC_TURN_LEFT){
//            dec_old = DEC_NO_TURN;
//            return DEC_TURN_LEFT;
//        }
//        else{
//            return DEC_NO_TURN;
//        }
//            
//    }
//}

void DEC_init(void){
    AD1PCFGL       |= 0x1800; /*Set AN11, AN12 to Digital Pins*/ 
    DEC_CHA_TRIS    = 1; /* input */
    DEC_CHB_TRIS    = 1; /* input */
    DEC_TASTE_TRIS  = 1; /* input */
    
    RPINR7bits.IC1R = 0b1011;   // RP11 mapped to Interrrupt Capture 1
    IC1CONbits.ICI = 0b00;      // interrupt every time
    IC1CONbits.ICM = 0b010;     // interrupt if falling edge
    
    IPC0bits.IC1IP = 0b010;     // interrupt priority
    IFS0bits.IC1IF = 0;
    IEC0bits.IC1IE = 1;          // interrupt enable   
}

state_rotation_t get_DEC_status(void){
    state_rotation_t tmp_state = DEC_NO_TURN;
    
    if(!DEC_TASTE_PORT && button_old == DEC_NO_TURN){
        button_old = DEC_BUTTON;
        return DEC_BUTTON;
    }
    else if(DEC_TASTE_PORT && button_old == DEC_BUTTON){
        button_old = DEC_NO_TURN;
        return DEC_NO_TURN;
    }
    else{
        tmp_state = state_rotation;
        state_rotation = DEC_NO_TURN;
        return tmp_state;
    }
}
    

void _IC_NO_PSV  _IC1Interrupt(void){
    if (DEC_CHB_PORT == 0){
        state_rotation = DEC_TURN_LEFT;
    }
    else{
        state_rotation = DEC_TURN_RIGHT;
    }
	IFS0bits.IC1IF = 0;                  // clear interrupt flag
}

