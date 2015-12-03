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
 * @version     0.2
 *
 */


#include <xc.h>

#include "global.h"
#include "DEC_API.h"

static char dec_last = 0x00;

void DEC_init(void){
    AD1PCFGL       |= 0x1800; /*Set AN11, AN12 to Digital Pins*/ 
    DEC_CHA_TRIS    = 1; /* input */
    DEC_CHB_TRIS    = 1; /* input */
    DEC_TASTE_TRIS  = 1; /* input */
    dec_last        = (!DEC_CHB_PORT <<1) | (!DEC_CHA_PORT);
}

//unsigned char get_DEC_button(){
//    if(DEC_TASTE_PORT) return 1;
//    else               return 0;
//}

unsigned char get_DEC_button(void){
    return (!DEC_TASTE_PORT);
}

state_rotation_t get_DEC_status(void){
    char dec_inp = 0x00;
    
    if(!DEC_TASTE_PORT){
        return DEC_BUTTON;
    }
    else{
        dec_inp = (!DEC_CHB_PORT <<1) | (!DEC_CHA_PORT);
        
        if(dec_inp == dec_last){
            return DEC_NO_TURN;
        }
        
        dec_inp  = dec_inp + dec_last;
        dec_last = dec_inp - dec_last;
        
        if((dec_inp == 0x02) || (dec_inp == 0x04) ){
            return DEC_TURN_LEFT;
        }
        else if((dec_inp == 0x01) || (dec_inp == 0x05) ){
            return DEC_TURN_RIGHT;
        }
        else{
            return DEC_NO_TURN;
        }
    }  
}





