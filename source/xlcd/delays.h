#ifndef __DELAYS_H
#define __DELAYS_H

#define Fcy 4000000

#define Delay_60nS_Cnt    (Fcy * 0.00000006)
#define Delay_150nS_Cnt   (Fcy * 0.00000015)
#define Delay_360nS_Cnt   (Fcy * 0.00000036)
#define Delay_450nS_Cnt   (Fcy * 0.00000045)
#define Delay_600nS_Cnt   (Fcy * 0.0000006)
#define Delay200uS_count  (Fcy * 0.0002)
#define Delay_1mS_Cnt     (Fcy * 0.001)
#define Delay_2mS_Cnt     (Fcy * 0.002)
#define Delay_5mS_Cnt     (Fcy * 0.005)
#define Delay_15mS_Cnt    (Fcy * 0.015)
#define Delay_1S_Cnt      (Fcy * 1)


/* delays specific to each LCD type */
/* delay btw RS/RW signal to E signal */
#define DelayRSSetupTime_Cnt     Delay_60nS_Cnt
/* delay btw E rise and Data available */
#define DelayDBOutput_Cnt        Delay_360nS_Cnt
/* min E pulse width low */
#define DelayEPulseWidthLow_Cnt  Delay_150nS_Cnt 
/* min E pulse width high */
#define DelayEPulseWidthHigh_Cnt Delay_450nS_Cnt
/* E pulse cycle time */
#define DelayEPulseWidth_Cnt     Delay_600nS_Cnt
/* min Power On Reset time */
#define DelayPORXLCD_Cnt         Delay_15mS_Cnt
/* generic delay for LCD */
#define DelayXLCD_Cnt            Delay_5mS_Cnt


/* C18 cycle-count delay routines. */

/* Delay of exactly 1 Tcy */
#define Delay1TCY() _delay(1)

/* Delay of exactly 10 Tcy */
#define Delay10TCY() _delay(10)

/* Delay1TCYx */
void Delay1TCYx(unsigned char);

/* Delay10TCYx
 * Delay multiples of 10 Tcy
 * Passing 0 (zero) results in a delay of 2560 cycles.
 */
void Delay10TCYx(unsigned char);

/* Delay100TCYx
 * Delay multiples of 100 Tcy
 * Passing 0 (zero) results in a delay of 25,600 cycles.
 */
void Delay100TCYx(unsigned char);

/* Delay1KTCYx
 * Delay multiples of 1000 Tcy
 * Passing 0 (zero) results in a delay of 256,000 cycles.
 */
void Delay1KTCYx(unsigned char);

/* Delay10KTCYx
 * Delay multiples of 10,000 Tcy
 * Passing 0 (zero) results in a delay of 2,560,000 cycles.
 */
void Delay10KTCYx(unsigned char);

#endif
