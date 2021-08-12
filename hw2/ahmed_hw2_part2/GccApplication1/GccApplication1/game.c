/*
 * CFile1.c
 *
 * Created: 10/1/2019 8:44:51 PM
 *  Author: alhaj1
 */ 
#include "game.h"


/*
void StripEOL(char string[],int n){
	
	for (int i =0 ; i < n ; i++){
		printf("%c ", string[i]);
		if(string[i] == "\n" || string[i] == "\r"){
			
		string[i] = "\0";	
		}
		printf("\n");
	}
}

*/



//#############################################//
// helper functions

//#############################################//

char * add_silence_char(const char arr[]){
	char *arr2 = (char*) malloc((strlen(arr)+2) * sizeof(char)+1);
	arr2 = NULL;
	strcat(arr2, arr);
	return strcat(arr2, "R0");
}

void delay_ms(int ms){
	while(ms-- ){
		_delay_ms(1);
		
	}
}
int is_silence(char ascii_letter, char duration){
	
	int res  = (ascii_letter == 'R' || ascii_letter == 'r')	&& (duration == 0);
	return res;
}


uint8_t get_char_freq(uint8_t letter){
	
	if( letter == (uint8_t)(NTA))
		return (uint8_t)(FREQ_A4_HZ) ;
	
	else if(letter== (uint8_t)(NTB))
		return (uint8_t)(FREQ_B4_HZ) ;
	
	else if(letter == (uint8_t)(NTC))
		return (uint8_t)FREQ_C4_HZ ;
	
	else if(letter == (uint8_t)(NTD))
		return (uint8_t)FREQ_D4_HZ ;
	
	else if(letter == (uint8_t)(NTE))
		return (uint8_t)FREQ_E4_HZ ;
	
	else if(letter == (uint8_t)(NTF))
		return (uint8_t)FREQ_F4_HZ ;
	
	else if(letter == (uint8_t)(NTG))
		return (uint8_t)FREQ_G4_HZ ;
	
	else if(letter == (uint8_t)(NTR))
		return (uint8_t)FREQ_A4_HZ ;
		
	return 0;
}




	
	

uint8_t PackNote (char letterASCII, uint8_t duration){
	
	if( letterASCII =='A' || letterASCII== 'a')
		return (uint8_t)(NTA << 5) + duration ;
		
	else if(letterASCII =='B'  || letterASCII== 'b')
		return (uint8_t)(NTB << 5) + duration ;
		
	else if(letterASCII =='C' || letterASCII == 'c')
		return (uint8_t)(NTC << 5) + duration ;
		
	else if(letterASCII =='D' || letterASCII == 'c')
		return (uint8_t)(NTD << 5) + duration ;
		
	else if(letterASCII =='E' || letterASCII == 'e')
		return (uint8_t)(NTE << 5) + duration ;
		
	else if(letterASCII =='F' || letterASCII == 'f')
		return (uint8_t)(NTF << 5) + duration ;
		
	else if(letterASCII =='G' || letterASCII == 'g')
		return (uint8_t)(NTG << 5) + duration ;
		
	else if(letterASCII =='R' || letterASCII == 'r')
		return (uint8_t)(NTR << 5) + duration ;
	
	
	
	return 0;
}

uint8_t UnpackNoteLetterASCII (uint8_t packedNote){
		
		// just to make sure stays 8bit
		return  (uint8_t) packedNote >> 5;
	
}

uint8_t UnpackNoteDuration (uint8_t packedNote){
	
	return (uint8_t) (packedNote & 0x1F);
}
/*
void StoreSong(uint8_t song[],const char songString[]){
	size_t song_len = strlen(songString);
	uint8_t counter = 0;
	
	for (uint8_t i = 0; i < song_len ; i+=2){
		if(!! isdigit(songString[i+1]) && !!songString[i+2]){
			
			uint8_t duration = (uint8_t)(songString[i+1] -'0')* 10 +(songString[i+2]-'0'); 
			
			song[counter] = PackNote(songString[i], duration);
			i++;	
		}else{
			
			if(is_silence(songString[i], songString[i+1])){
				
				song[counter] = (uint8_t)(NTR << 5);
				
				}		
			counter++;
			
		}
	
	}
}
*/
void PlayNote(uint8_t letterASCII, uint8_t quarters){
	
	uint8_t freq = get_char_freq(letterASCII);
	int note_itrs = freq / (4 * quarters);
	uint32_t hf_period = (HALFPERIOD_G4_US * quarters);
	for(int i = 0 ; i < note_itrs; i++){
		
			  PORTB = (PORTB_MASK & 0x00);
			  delay_ms(hf_period);

			  // set port B pin 5 high, and delay for half_period ms
			  PORTB = (PORTB_MASK & 0xFF);
			  delay_ms(hf_period);
		
	}    
	
}

void PlaySong(uint8_t song[]){
	
	  uint8_t note, duration;

	  // loop until the termination of a song
	  for (size_t i = 0; song[i] != NULL_SONG; i++) {

		  // unpack the ASCII character and duration of the note
		  note = UnpackNoteLetterASCII(song[i]);
		  printf("note = %uc \n", note); 
		  duration = UnpackNoteDuration(song[i]);
		  printf("duration = %hu \n ", duration);
		  // play the note after being unpacked
		  PlayNote(note, duration);

	  }

  }	


