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


static state_rotation_t button_old = DEC_NO_TURN;
static state_rotation_t dec_old = DEC_NO_TURN;

void DEC_init(void){
    AD1PCFGL       |= 0x1800; /*Set AN11, AN12 to Digital Pins*/ 
    DEC_CHA_TRIS    = 1; /* input */
    DEC_CHB_TRIS    = 1; /* input */
    DEC_TASTE_TRIS  = 1; /* input */
}

unsigned char get_DEC_button(void){
    if(!DEC_TASTE_PORT && button_old == DEC_NO_TURN){
        button_old = DEC_BUTTON;
        return DEC_BUTTON;
    }
    else if(DEC_TASTE_PORT && button_old == DEC_BUTTON){
        button_old = DEC_NO_TURN;
        return DEC_NO_TURN;
    }
    else
        return DEC_NO_TURN;
}

state_rotation_t get_DEC_status(void){
    uint16_t dec_inp = 0x00;
    
    if(!DEC_TASTE_PORT && button_old == DEC_NO_TURN){
        button_old = DEC_BUTTON;
        return DEC_BUTTON;
    }
    else if(DEC_TASTE_PORT && button_old == DEC_BUTTON){
        button_old = DEC_NO_TURN;
        return DEC_NO_TURN;
    }
    else{
        dec_inp = (DEC_CHB_PORT <<4) | (DEC_CHA_PORT);
        if(dec_inp ==0x10 && dec_old == DEC_NO_TURN){
            dec_old = DEC_TURN_RIGHT;
            return DEC_NO_TURN;
        }
        else if(dec_inp ==0x11 && dec_old == DEC_TURN_RIGHT){
            dec_old = DEC_NO_TURN;
            return DEC_TURN_RIGHT;
        }
        else if(dec_inp == 0x00 && dec_old == DEC_NO_TURN){
            dec_old = DEC_TURN_LEFT;
            return DEC_NO_TURN;
        }
        else if(dec_inp ==0x11 && dec_old == DEC_TURN_LEFT){
            dec_old = DEC_NO_TURN;
            return DEC_TURN_LEFT;
        }
        else{
            return DEC_NO_TURN;
        }
            
    }
}





