/** 
 * @file        PLL_API.h
 *
 * @brief       PLL_API contains the PLL basic functions
 * 
 * @author      Florian Heidecker
 * @date        13.11.2015 - initial version
 *              07.12.2015 - rework/comments
 * 
 * @version     0.1
 */

#ifndef _PLL_API_H
#define _PLL_API_H

#include <xc.h>

//== typedefs ==================================================================

/** avalible frequenz output on SCKO1 in MHz */
typedef enum {PLL_SCKO1_16MHz = 1, PLL_SCKO1_33MHz = 0} PLL_scko1_freq_t;

/** avalible sampling frequency in kHz */
typedef enum {PLL_SAMPLING_FREQ_48kHz=0,
              PLL_SAMPLING_FREQ_44_1kHz=1,
              PLL_SAMPLING_FREQ_32kHz=2,
              PLL_SAMPLING_FREQ_96kHz=4,
              PLL_SAMPLING_FREQ_88_2kHz=5,
              PLL_SAMPLING_FREQ_64kHz=6} PLL_sampling_freq_t;

//== functions =================================================================

/**
 * @brief       set TRIS, PLL default output frequenzies
 */
void PLL_init(void);

/**
 * @brief       set SCKO1 output frequency
 * 
 * @param PLL_scko1_freq        see
 *                              avalible frequenz output on SCKO1 in MHz
 *                              -> PLL_scko1_freq_t
 */
void PLL_set_scko1_freq(PLL_scko1_freq_t PLL_scko1_freq);

/**
 * @brief       get actuel SCKO1 output frequency
 * 
 * @return      see
 *              avalible frequenz output on SCKO1 in MHz
 *              -> PLL_scko1_freq_t
 */
PLL_scko1_freq_t PLL_get_scko1_freq(void);

/**
 * @brief       set SCKO2 and SCKO3 output frequency
 *              both SCKO are connected together
 *              formula (fs = PLL_sampling_freq):
 *                          SCKO2_output = fs * 256
 *                          SCKO3_output = fs * 384
 * 
 * @param PLL_sampling_freq     see
 *                              avalible sampling frequency in kHz
 *                              -> PLL_sampling_freq_t
 */
void PLL_set_sampling_freq(PLL_sampling_freq_t PLL_sampling_freq);

/**
 * @brief       get actuel sampling frequency for SCKO2 and SCKO3 output
 *              frequency
 *              both SCKO are connected together
 *              formula (fs = PLL_sampling_freq):
 *                          SCKO2_output = fs * 256
 *                          SCKO3_output = fs * 384
 * 
 * @return     see
 *             avalible sampling frequency in kHz
 *             -> PLL_sampling_freq_t
 */
PLL_sampling_freq_t PLL_get_sampling_freq(void);

#endif /* _PLL_API_H */



