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

#ifndef _DEC_API_H
#define _DEC_API_H

#include <xc.h>

/** State of rotation */
typedef enum {DEC_TURN_LEFT=0,
              DEC_NO_TURN=1,
              DEC_TURN_RIGHT=2} state_rotation_t;

/** Rotary Encoder PINS TRIS initialization */
void DEC_init();

/** Get the State of the Rotary Encoder Button */
unsigned char get_DEC_button();

/** Get the State of the Rotation */
state_rotation_t get_DEC_rotation();


#endif /* _DEC_API_H */
