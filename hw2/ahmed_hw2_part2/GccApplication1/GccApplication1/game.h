/*
 * CFile1.c
 *
 * Created: 10/1/2019 8:41:46 PM
 *  Author: alhaj1
 */ 

#ifndef _GAME_H_
#define _GAME_H_

#include "uart.h"
//#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

extern FILE uart_stream;
//stderr = stdin = stdout = &uart_stream;

#define MAX_PASS_LENGTH 128 
#define NUMBER_OF_SONGS 4
#define SONG_LENGTH 64
#define TITLE_LENGTH 32

#define NUMBER_OF_SONGS 4
#define FREQ_G4_HZ 392



#define NTA 0
#define NTB 1
#define NTC 2
#define NTD 3
#define NTE 4
#define NTF 5
#define NTG 6
#define NTR 7
#define NULL_SONG (NTR <<5)



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




char user_line[MAX_PASS_LENGTH];
//char buff[MAX_PASS_LENGTH];

//enum {false, true} BOOL;

//#############################################//
// helper functions

//#############################################//

/*
typedef struct Song{
	
	int m_song_len;
	char* m_song_str;
	char* m_song_title; 		
	
	}Song;

*/
//void StripEOL(char string[],int n);
	
char * add_silence_char(const char arr[]);


//############################################

//############################################
void delay_ms(int ms);


//############################################

//############################################

void print_menu(const char menu[]);
int is_silence(char x, char y);

void song_menu(char *song_titles);

uint8_t make_menu(char* song_titles);

int best_match(char user[], char *song_title_list);

uint8_t get_char_freq(uint8_t ascii );


//uint8_t DisplayMenu(const char menu[]);

uint8_t PackNote (char letterASCII, uint8_t duration);

uint8_t UnpackNoteLetterASCII (uint8_t packedNote);

uint8_t UnpackNoteDuration (uint8_t packedNote);

//void StoreSong(uint8_t song[],const char songString[]);

void PlayNote(uint8_t letterASCII, uint8_t quarters);

void PlaySong(uint8_t song[]);

//void play_menu(const char menu[], char* song_titles);


#endif