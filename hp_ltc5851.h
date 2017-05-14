/* 
 * File:   hp-ltc5851.h
 * Author: dkg
 *
 * Created on May 13, 2017, 6:56 PM
 */

#ifndef HP_LTC5851_H
#define	HP_LTC5851_H

#ifdef	__cplusplus
extern "C" {
#endif

  void HPltc5851DisplayTask(void);
  int Display(char * );

  // Order of connection A..G, DP.
#define NUM_0 0b11000000
#define NUM_1 0b11111001
#define NUM_2 0b10100100  
#define NUM_3 0b10110000
#define NUM_4 0b10011001
#define NUM_5 0b10010010
#define NUM_6 0b10000010
#define NUM_7 0b11111000
#define NUM_8 0b10000000
#define NUM_9 0b10010000
  
#define ALPHA_A 0b10001000     
#define ALPHA_B 0b10000011     
#define ALPHA_C 0b11000110
#define ALPHA_D 0b10110001
#define ALPHA_E 0b10000110
#define ALPHA_R 0b10101111
#define ALPHA_H 0b10001001
#define ALPHA_T 0b10000111





#define DIGIT1_PORT IO_RA4_LAT 
#define DIGIT2_PORT IO_RA5_LAT
#define DIGIT3_PORT IO_RA6_LAT
#define DIGIT4_PORT IO_RA7_LAT

#define MULTIPLEXER LATC
#ifdef	__cplusplus
}
#endif

#endif	/* HP_LTC5851_H */

