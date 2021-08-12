/*
 * IncFile1.h
 *
 * Created: 11/16/2019 3:21:21 PM
 *  Author: alhaj1
 */ 

#include <avr/io.h>

#define LCD_REGISTER_COUNT      20

#define LCD_INITIAL_CONTRAST    0x0F

#define FALSE   0
#define TRUE    (!FALSE)

// LCD Data Register 0    // DEVICE SPECIFIC!!! (ATmega169)
#define pLCDREG ((unsigned char *)(0xEC))

// DEVICE SPECIFIC!!! (ATmega169) First LCD segment register
#define LCD_CONTRAST_LEVEL(level) LCDCCR=((LCDCCR&0xF0)|(0x0F & level))

//Functions
void LCD_Init (void);
void LCD_WriteDigit(char input, char digit);  //digit can be 0 to 5
void LCD_AllSegments(char show);
