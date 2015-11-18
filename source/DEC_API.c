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
 * @version     0.1
 *
 */


#include <xc.h>

#include "log.h"
#include "global.h"
#include "DEC_API.h"

void DEC_init(){
    PLL_LOG("rotencoder init\n");
    DEC_CHA_TRIS    = 1; /* input */
    DEC_CHB_TRIS    = 1; /* input */
    DEC_TASTE_TRIS  = 1; /* input */
}

//unsigned char get_DEC_button(){
//    if(DEC_TASTE_PORT) return 1;
//    else               return 0;
//}

unsigned char get_DEC_button(){
    return DEC_TASTE_PORT;
}

state_rotation_t get_DEC_rotation(){
    static char dec_last = 0x00;
    char dec_inp = 0x00;
    
    if(DEC_CHA_PORT){
        dec_inp = 0x01;
    }
    if(DEC_CHB_PORT){
        dec_inp ^= 0x03;
    }
    dec_inp -= dec_last;
    if(dec_inp & 0x01){
        dec_last += dec_inp;
        return ((dec_inp & 0x02));
    }
    else{
        return DEC_NO_TURN;
    }  
}





