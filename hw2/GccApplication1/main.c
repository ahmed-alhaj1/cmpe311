/*
 * CMPE 311
 * F19 Discussion 5
 * Created: 9/27/2019 1:17:11 PM
 */

#include "uart.h"
#include <string.h>
#include <avr/io.h>
#include "music.h"

//extern FILE uart_stream; /* declare uart_stream indicating that it is defined within project scope */

// constant char arrays transmitted via serial
const char menu[] ="----- MAIN MENU -----|1.List Shows|2.Play Show|3.Create Show|Please Enter a Choice:|";
const char show_list[] ="----- SHOW LIST -----|0.Title: Hot Cross Buns|1.Title: Mary Little Lamb|3.Title: Twinkle Little Start|4.Title: Wheels on the bus|";
const char ply_menu[] = "----- Play by MENU -----|1.Play by Number|2.Search by Title|3.Please Enter a Choice:|";

 /* maximum length of user defined password */




int main(void)
{
	stderr = stdin = stdout = &uart_stream; /* re-map standard output, input, error */

	UARTInit(); /* initialize the UART (set hardware specific configuration registers) */

	//printf(promptEncrypt);
	//printf("%s \n", menu);

	//char input[MAX_PASS_LENGTH]; /* char array to store user defined password */
	//char guess[MAX_PASS_LENGTH]; /* char array to store user's password guess */

	uint8_t input = DisplayMenu(menu);
	//enum BOOL sentinel = false;
	//do{



	//}while(sentinel == false);
	//fgets(input, MAX_PASS_LENGTH, &uart_stream); /* user sets password */

	 /* encrypt password */


	//fgets(guess, MAX_PASS_LENGTH, &uart_stream); /* user attempts to enter correct password */


	/* [INSTRUCTIONS]: compare the decrypted password to the user's
	   input using function strcmp(const char* str1, const char* str2)

	   strcmp returns:
	   (int = 0): strings are identical
	   (int > 0): first non-matching char in str1 > str2
	   (int < 0): first non-matching char in str1 < str2

	   loop and re-prompt the user to enter a password while
	   their entry does not match the decrypted password, when
	   the passwords match the loop should exit and the secret
	   message will be transmitted
	*/

	// transmits secret message


	return 0;
}
