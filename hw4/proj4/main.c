

/*
* Instructions:
*	1. Read through the following code and take note of the difference between lcd_puts_P and lcd_puts
*	2. Build (don't run or debug) the code using the function lcd_puts
*	3. Note the Program Memory Usage and Data Memory Usage in the build output
*	4. Change the code to call lcd_puts_P instead of lcd_puts using the same string (simply uncomment lcd_puts_P in main and comment lcd_puts)
*	5. Note the Program Memory Usage and Data Memory Usage in the build output
*	6. What changes happened and why?
*	7. Play around with creating strings stored in program memories
*
*/


#define F_CPU 8000000
#include <avr/pgmspace.h>

#include <stdlib.h>

// AVR libraries
#define MIN_PULSE_WIDTH 10
#include <avr/interrupt.h>
#include "U0_UART.h"
#include <string.h>
#include<avr/io.h>
//#include <avr/io.h>

#include <util/delay.h>
#include "U0_LCD_Driver.h"
extern FILE uart_stream; 

#define PINB_MASK ( ( 1 << PINB7 ) | ( 1 << PINB6 ) )
//| ( 1 << PINB4 ) )
#define PINE_MASK ( ( 1 << PINE3 ) | ( 1 << PINE2 ) )


volatile uint8_t ServoPos = 0 ;
int INITADC;


void servo_init(void);

uint8_t press_up(void);

uint8_t press_down(void);

uint8_t press_right(void);

// ------------------ ADC FUNCTIONS ------------------


uint16_t get_adc();

int adc_acquire();
// ------------------ SERVO FUNCTIONS ------------------

void follow_the_light(void);

void avoid_the_light(void);

// ------------------ HELPER FUNCTIONS ------------------

uint8_t max3(uint8_t, uint8_t, uint8_t);


// ------------------ FUNCTION IMPLEMENTATIONS ------------------
ISR(PCINT1_vect) {

    // for storing previous value of port to detect
    static uint8_t pinBPrev = 1;

    // toggle PORTB0 based on center button status being newly pressed, but
    // not when it is released
    if (((PINB & (1 << 4)) == 0) && ((pinBPrev & (1 << 4)) != 0)) {
        // if button pressed (bit is zero) and previous it wasn't
        PORTB ^= (1 << 0);  // toggle led on B0
    }

    pinBPrev = PINB;  // save button status
}

void lcd_puts_P(const char  c[]) { //same const char *c
	uint8_t ch = pgm_read_byte(c);
	int location = 0;
	while(ch != 0) {
		LCD_WriteDigit(ch, location);
		ch = pgm_read_byte(++c);
		location ++;
	}
}

void lcd_puts(const char  c[]) { //same const char *c
	uint8_t ch = *c;
	int location = 0;
	while(ch != 0) {
		LCD_WriteDigit(ch, location);
		ch = *(++c);
		location ++;
	}
}

/*
 * Sends signals to the servo to move by the inputted variable degree
 */

void move_servo(int degrees) {

    //PORTB &= ((uint8_t)degrees & 0b00100000);
	OCR0A += degrees;

}

/*
 * Initializes all interrupts utlitized in the program
 */
void interrupts_init(void) {
    // setup for center button interrupt

    // unmask bit for Center Button on Butterfly, PB4->PCINT12 to allow it
    // to trigger interrupt flag PCIF1
    PCMSK1 |= (1 << PCINT12);
    EIMSK = (1 << PCIE1);    // enable interrupt for flag PCIF1

}
/*
 * Initializes all pins utlitized in the program
 */

void joy_init(void){
	
	DDRB &= ( ~PINB_MASK );
    PORTB |= PINB_MASK;

    DDRE &= ( ~PINE_MASK );
    PORTE |= PINE_MASK;
}

void servo_init(void){
	
	//#define PORTB5_MASK 0b00100000
	DDRB |= (1 << PB4);
	//DDRB = 0b00010000 ;	
}

void pins_init(void) {

    // set B6, B7 as inputs, corresponding to the joystick UP and DOWN buttons
    DDRB &= ~(0b11100000);
    // set E2, E3 as inputs, corresponding to the joystick RIGHT button
    DDRE &= ~(0b00001000);

    // enable pull up resistors on B5, B6, B7
    PORTB |= 0b11100000;
    // enable pull up resistor on pin E2, E3
    PORTE |= 0b00001000;

    // setup output for servo
    // enable PORTB5 as output
    //DDRB |= (1 << 5);
    // enable PORTB0 as output for the first LED
    DDRB |= (1 << 0);
    // enable PORTB1 as output for the second LED
    DDRB |= (1 << 1);

    // setup the interrupts
    interrupts_init();
    // enable global interrupts
    sei();

}

void follow_the_light() {
	lcd_puts("FL LG");
	//printf("I am at follow light ");
	uint8_t angle_prev, angle_next;

	move_servo(-10);
	angle_prev = adc_acquire();
	//printf("angle prev = %d \n",angle_prev);
	move_servo(angle_prev);
	_delay_ms(500);

	move_servo(20);
	angle_next = adc_acquire();
	_delay_ms(500);

	// local sweep
	uint8_t optimal_angle = max3(INITADC, angle_prev, angle_next);
	//lcd_puts_P((char *) optimal_angle);
	printf("optimal angle %d \n ", (int)optimal_angle);

	// full sweep
	while (adc_acquire() < optimal_angle) {
		_delay_ms(500);
		move_servo(20);
	}


}
void avoid_the_light() {
	printf("I am at avoid light");
	lcd_puts("RV LG");
	uint8_t angle_prev, angle_next;
	printf(" adc_acquire() = %hhu  \n", adc_acquire());
	move_servo(-10);
	angle_prev = adc_acquire();
	
	_delay_ms(500);

	move_servo(20);
	angle_next = adc_acquire();
	_delay_ms(500);

	// local sweep
	uint8_t optimal_angle = max3(INITADC, angle_prev, angle_next);
	//lcd_puts_P((char *) optimal_angle);
	printf("optimal angle =%d , prev_angle = %d , next_angle = %d \n", optimal_angle, angle_prev, angle_next );

	// full sweep
	while (adc_acquire() > optimal_angle) {
		printf("adc_acquire() = %hhu ", adc_acquire());
		_delay_ms(500);
		move_servo(20);
	}
}

void ADCSetup(){
	// AVR Butteryfly Board Info:
	// The Neg. Temp. Coeff. resistor (NTC)      is on ADC channel 0
	// The Board Edge Voltage Input Reading (VR) is on ADC channel 1
	// The Light Dependant Resistor (LDR)        is on ADC channel 2


	//Disable Digital Input Buffer on pins being used for analog input to save power
	//    using the Digital Input Disable Register
	DIDR0 |= 0b00000001; //disable PF0 (ADC0) digital input buffer


	//Select Voltage Reference, Set Left-Ship Option, Set Input Channel
	int refSel_2b=1;    //select avcc, change to 3 for 1.1V reference
	int adlar_1b=0;     //no need to left shift
	int muxSel_5b = 5;  //select ADC0 with single-ended conversion
	ADMUX = (refSel_2b << REFS0) + (adlar_1b<<ADLAR) + (muxSel_5b << MUX0);

	//enable adc and with interrupt disabled
	ADCSRA = (1<<ADEN) + (0 << ADSC) + (0 << ADATE) + (0 << ADIF) + (0<< ADIE) + (0 <<ADPS0);

	//Set auto conversion source
	//ADCSRB &= 0b11111000; //autoconversion (ADATAE) not set so trigger source is not used
}

//Call this function to start an ADC conversion
void ADCStartConversion(){
	ADCSRA |= 1 << ADSC; //this is automatically cleared
}

void ADCClearConversionFlag(){
	ADCSRA |= (1<<ADIF); //all interrupt flags are cleared by writing a one
}

int ADCIsConversionCompleteFlagSet(){
	printf("I am at adc convert complete \n");
	uint8_t res = (ADCSRA &(1<< ADIF));
	
	printf( "res = %d ", (int)res );
	return(ADCSRA & (1<<ADIF));
}

// modify this command to return ADC, value.  Hint: you can access it by using the macro symbol ADC.  Note, if accessing the high and low bytes individually, access ADCL first then ADCH
uint16_t ADCGet(){
	return ADC;
}

int adc_acquire(){
	printf("I am at adc acquired \n");
	ADCClearConversionFlag();
	ADCStartConversion();
	while(ADCIsConversionCompleteFlagSet() );
	uint16_t acd_val =  ADCGet();
	printf("adc = %d \n", (int)acd_val);
	return acd_val;
}




void timer0_init(void){
	//TCCR0A = (1<<CS00) | (1<<CS02);
	TCCR0A = 0b01100100;
	//printf("");
	TCNT0 = 0;
	OCR0A = 15;
	
	}


/*
 * Returns the value of ADC after clearing all flags
 */


/*
 * Returns status of JOYSTICK UP
 */
uint8_t JoyGet ( void )
{
    uint8_t b = ( ( ~PINB ) & PINB_MASK );
    return b | ( ( ~PINE ) & PINE_MASK );
}


uint8_t press_up() {

    return (PORTB & 0b10000000);

}


/*
 * Returns status of JOYSTICK DOWN
 */
uint8_t press_down() {

    return (PORTB & 0b01000000);

}


/*
 * Returns status of JOYSTICK RIGHT
 */

timer1_init(){
	
	
}
uint8_t press_right() {

    return (PORTE & 0b00001000);

}



/*
 * Returns the maximum of 3 integers
 */
uint8_t max3(uint8_t a, uint8_t b, uint8_t c) {

    uint8_t m = a;

    // simple boolean expressions for fast comparison
    (void) ((m < b) && (m = b));
    (void) ((m < c) && (m = c));

    return m;

}



int main(void)
{
	
	stderr = stdin = stdout = &uart_stream;
	UARTInit(); 
	
	printf("welcome to proj4 servo \n");
	LCD_Init();
	lcd_puts("HEllo");
	_delay_ms(1000);
	//servo_init();
	//                             adc_init();
	//timer0_init();
	pins_init();
	//INITADC = adc_acquire();
	joy_init();
	//#####################
	DDRD = 0xFF;
    PORTD = 254;
    
    PORTD = 255;
	
	//move_servo(20);
	//_delay_ms(10000);
	timer0_init();
	servo_init();
	uint8_t joy_val = JoyGet();
	uint8_t r_click = press_right();
	
	uint8_t mode = 0;
	
	//move_servo(-10);
	while(joy_val != r_click ){
		r_click = press_right();
		joy_val = JoyGet();
		
	
		printf("joy_val = %d \n", joy_val);
		printf("right_click = %d ", r_click);
		
		if (joy_val == press_up()) {
            mode++;
			lcd_puts("FLG");
			printf("mode = %d \n",mode);
			_delay_ms(1000);
			
        } else if (joy_val == press_down()) {
            mode--;
			printf("mode =%d \n", mode);
			lcd_puts("RVLG");
			_delay_ms(1000);
			
        }
		

		// display menu string depending on value of mode
        (mode % 2) ? printf("following light \n") : printf("reverse light \n");
		//printf("adc_read  = %d ", adc_val);
		 _delay_ms(1000);
	}
		printf("mode %d \n", mode);
		(mode % 2) ? follow_the_light() : avoid_the_light();
		_delay_ms(1000);

    // wait a sufficient amount of time before termination
    //_delay_ms(10000);

    return EXIT_SUCCESS;
	
}


