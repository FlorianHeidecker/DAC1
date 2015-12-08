/** 
 * @file        CONTROL.h
 *
 * @brief       CONTROL controls all input and output set and get function
 * 
 * @author      Florian Heidecker
 * @date        07.12.2015 - initial version
 * 
 * @version     0.1
 */

#ifndef _CONTROL_H
#define	_CONTROL_H

#include <xc.h>

void CONTROL_init(void);

void CONTROL_set_attunation_level(uint8_t value);

uint8_t CONTROL_get_attunation_level(void);

void CONTROL_set_soft_mute(uint8_t value);

uint8_t CONTROL_get_soft_mute(void);

void CONTROL_set_zero_detect_mute(uint8_t value);

uint8_t CONTROL_get_zero_detect_mute(void);

void CONTROL_set_monaural_mode(PCM_monaural_mode_t PCM_monaural_mode);

PCM_monaural_mode_t CONTROL_get_monaural_mode(void);

uint8_t CONTROL_get_zero_detection(void);

#endif	/* _CONTROL_H */

