/** 
 * @file        CONTROL.h
 *
 * @brief       CONTROL controls all input and output set and get function
 * 
 * @author      Florian Heidecker
 * @date        07.12.2015 - initial version
 *              08.12.2015 - PCM function implementation
 * 
 * @version     0.1
 */

#ifndef _CONTROL_H
#define	_CONTROL_H

#include <xc.h>
#include "PCM_API.h"

//== typedefs ==================================================================
typedef enum {	no_zero_detection=0,
				left_zero_detection=1,
				right_zero_detection=2,
				left_right_zero_detection=3} CONTROL_zero_detection_t;

//== functions =================================================================

void CONTROL_init(void);

void CONTROL_set_attunation_level(uint8_t percent);

uint8_t CONTROL_get_attunation_level(void);

void CONTROL_set_soft_mute(uint8_t value);

uint8_t CONTROL_get_soft_mute(void);

void CONTROL_set_zero_detect_mute(uint8_t value);

uint8_t CONTROL_get_zero_detect_mute(void);

void CONTROL_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode);

PCM_monaural_mode_t CONTROL_get_monaural_mode(void);

CONTROL_zero_detection_t CONTROL_get_zero_detection(void);

#endif	/* _CONTROL_H */

