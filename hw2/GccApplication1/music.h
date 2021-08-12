/*
 * CFile1.c
 *
 * Created: 10/1/2019 8:41:46 PM
 *  Author: alhaj1
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "uart.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

extern FILE uart_stream;

#define MAX_PASS_LENGTH 128
#define FREQ_G4_HZ 392
#define HALFPERIOD_G4_US 1276


#define NTA 0
#define NTB 1
#define NTC 2
#define NTD 3
#define NTE 4
#define NTF 5
#define NTG 6
#define NTR 7



#define HALFPERIOD_G4_US 1276
#define PORTB_MASK 0x20
#define FREQ_A4_HZ 440
#define FREQ_B4_HZ 494
#define FREQ_C4_HZ 262
#define FREQ_D4_HZ 294
#define FREQ_E4_HZ 330
#define FREQ_F4_HZ 350
#define FREQ_G4_HZ 392
#define FREQ_R_HZ  4


enum BOOL{false, true};
char user_line[MAX_PASS_LENGTH];
//#############################################//
// helper functions

//#############################################//
char * set_silence_char(const char arr[]);


//############################################

//############################################
void delay_ms(int ms);


//############################################

//############################################

int is_silence(char x, char y);




uint8_t get_char_freq(uint8_t ascii );



uint8_t DisplayMenu(const char menu[]);

uint8_t PackNote (char letterASCII, uint8_t duration);

uint8_t UnpackNoteLetterASCII (uint8_t packedNote);

uint8_t UnpackNoteDuration (uint8_t packedNote);

void StoreSong(uint8_t song[],const char songString[]);

void PlayNote(uint8_t letterASCII, uint8_t quarters);

void PlaySong(uint8_t song[]);


#endif
