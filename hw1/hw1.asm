;
; AssemblerApplication2.asm
;
; Created: 9/16/2019 4:14:47 PM
; Author : alhaj1
;

/*
 * uart.asm
 *
 */ 

;Simple program to send "Hello! World" using AVR Butteryfly @ default 8Mhz
;runs 4800 buad with 2 stop bits and no partiy
.NOLIST
.include "M169PDEF.INC"
.LIST

.def A = R20
.def val = R2 
.def code_val = R19
.def PORTDEF =R22 
.def COUNTER1 = R23
.def COUNTER2 = R24
.def COUNTER3 = R25
 
.def TEMP=r16
.def TEMP0=r17
.def TEMP1=r18
.ORG $0000
	RJMP START





; Initialize Stack Pointer to end of RAM
;LDI TEMP, HIGH(RAMEND) ; Upper byte
;OUT SPH,TEMP ; to stack pointer
;LDI TEMP, LOW(RAMEND) ; Lower byte
;OUT SPL,TEMP; to stack pointer

USART_Init:

;Load UBRRH with 0 and UBRRL with 103
;in other words FOSC/16/BAUD-1
;to set a baud rate of about 4800 at 8MHz
ldi TEMP,00
//mov UBRRH, TEMP ; can't do this since UBRRH is in the _extended_ i/o
sts UBRRH,TEMP
ldi TEMP,103
sts UBRRL,TEMP
;Clear all error flags
ldi TEMP,00
sts UCSRA,TEMP
;Enable Transmission and Reception
ldi TEMP,(1<<RXEN0)|(1<<TXEN0)
sts UCSRB,TEMP
; Set frame format: 8data, 2stop bit
ldi TEMP, (1<<USBS0)|(3<<UCSZ00)
sts UCSR0C,TEMP
ret 

;Transmit Data
USART_Transmit_H:
;Wait for empty transmit buffer
;sbis UCSR0A,UDRE ; can't do this
;rjmp USART_Transmit_H ; and this since UCSR0A is extended i/o
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_H
; send the data
ldi TEMP, 0x48
sts UDR0, TEMP
ret


USART_Transmit_I:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_I
; send the data
ldi TEMP, 0x49
sts UDR0, TEMP
ret

USART_Transmit_G:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_G
; send the data
ldi TEMP, 0x47
sts UDR0, TEMP
ret

USART_Transmit_E:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_E
; send the data
ldi TEMP, 0x45
sts UDR0, TEMP
ret

USART_Transmit_L:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_L
; send the data
ldi TEMP, 0x4C
sts UDR0, TEMP
ret

USART_Transmit_C:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_C
; send the data
ldi TEMP, 0x43
sts UDR0, TEMP
ret

USART_Transmit_O:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_O
; send the data
ldi TEMP, 0x4F
sts UDR0, TEMP
ret

USART_Transmit_W:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_W
; send the data
ldi TEMP, 0x57
sts UDR0, TEMP
ret

USART_Transmit_P:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_P
; send the data
ldi TEMP, 0x50
sts UDR0, TEMP
ret

USART_Transmit_S:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_S
; send the data
ldi TEMP, 0x53
sts UDR0, TEMP
ret

USART_Transmit_A:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_A
; send the data
ldi TEMP, 0x41
sts UDR0, TEMP
ret

USART_Transmit_T:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_T
; send the data
ldi TEMP, 0x54
sts UDR0, TEMP
ret

USART_Transmit_N:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_N
; send the data
ldi TEMP, 0x4E
sts UDR0, TEMP
ret

USART_Transmit_R:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_R
; send the data
ldi TEMP, 0x52
sts UDR0, TEMP
ret

USART_Transmit_U:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_U
; send the data
ldi TEMP, 0x55
sts UDR0, TEMP
ret

USART_Transmit_D:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_D
; send the data
ldi TEMP, 0x44
sts UDR0, TEMP
ret

USART_Transmit_F:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_F
; send the data
ldi TEMP, 0x46
sts UDR0, TEMP
ret

USART_Transmit_M:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_M
; send the data
ldi TEMP, 0x4D
sts UDR0, TEMP
ret

USART_Transmit_Y:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_Y
; send the data
ldi TEMP, 0x59
sts UDR0, TEMP
ret

USART_Transmit_V:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_V
; send the data
ldi TEMP, 0x56
sts UDR0, TEMP
ret

USART_Transmit_empty:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_empty
; send the data
ldi TEMP, 0x20
sts UDR0, TEMP
ret

USART_Transmit_exclamation:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_exclamation
; send the data
ldi TEMP, 0x21
sts UDR0, TEMP
ret

USART_Transmit_start_symbol:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit_start_symbol
; send the data
ldi TEMP, 0x23
sts UDR0, TEMP
ret

USART_transmit_new_line:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_transmit_new_line
; send the data
ldi TEMP, 0xA
sts UDR0, TEMP
ret

USART_transmit_write:
; Wait for empty transmit buffer
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_transmit_new_line
; send the data
ldi TEMP, 0xD
sts UDR0, TEMP
ret

; now send the data using a function call

DONE:
	;rcall print_DONE
rjmp DONE

USART_Transmit: ;assumes data is in register TEMP
; Wait for empty transmit buffer
;sbis UCSR0A,UDRE
lds TEMP0, UCSR0A
sbrs TEMP0,UDRE
rjmp USART_Transmit
; send the data
sts UDR0, TEMP
ret

;###################################################################
; the next at least 200 line of code are just print_statements, some are used to commincate with user, and some are used for debugging porpuses.

print_empty:
	RCALL USART_transmit_empty
	ret

print_hello:
	RCALL USART_transmit_H
	RCALL USART_transmit_E
	RCALL USART_transmit_L
	RCALL USART_transmit_L
	RCALL USART_transmit_O
	ret
print_please:
	RCALL USART_transmit_P
	RCALL USART_transmit_L
	RCALL USART_transmit_E
	RCALL USART_transmit_A
	RCALL USART_transmit_S
	RCALL USART_transmit_E
	ret

print_DONE:
	RCALL USART_transmit_D
	RCALL USART_transmit_O
	RCALL USART_transmit_N
	RCALL USART_transmit_E
	RCALL print_new_line
	ret

print_enter:
	RCALL USART_transmit_E
	RCALL USART_transmit_N
	RCALL USART_transmit_T
	RCALL USART_transmit_E
	RCALL USART_transmit_R
	ret
print_code:
	RCALL USART_transmit_C
	RCALL USART_transmit_O
	RCALL USART_transmit_D
	RCALL USART_transmit_E
	ret

print_new_line:
	RCALL USART_transmit_new_line
	RCALL USART_transmit_write
	ret
print_start:
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL USART_transmit_start_symbol
	RCALL print_new_line
	ret

print_up:
	RCALL USART_transmit_U
	RCALL USART_transmit_P
	RCALL USART_transmit_empty
	RCALL USART_transmit_empty
	RCALL print_new_line
	ret
print_down:
	RCALL USART_transmit_D
	RCALL USART_transmit_O
	RCALL USART_transmit_W
	RCALL USART_transmit_N
	RCALL USART_transmit_empty
	RCALL USART_transmit_empty
	ret
print_left:
	RCALL USART_transmit_L
	RCALL USART_transmit_E
	RCALL USART_transmit_F
	RCALL USART_transmit_T
	RCALL USART_transmit_empty
	RCALL USART_transmit_empty
	ret
print_right:
	RCALL USART_transmit_R
	RCALL USART_transmit_I
	RCALL USART_transmit_G
	RCALL USART_transmit_H
	RCALL USART_transmit_T
	RCALL USART_transmit_empty
	RCALL USART_transmit_empty
	ret

print_correct:
	RCALL USART_transmit_I
	RCALL USART_transmit_empty

	RCALL USART_transmit_A
	RCALL USART_transmit_M
	RCALL USART_transmit_empty

	RCALL USART_transmit_A
	RCALL USART_transmit_T
	RCALL USART_transmit_empty

	RCALL USART_transmit_C
	RCALL USART_transmit_O
	RCALL USART_transmit_R
	RCALL USART_transmit_R
	RCALL USART_transmit_E
	RCALL USART_transmit_C
	RCALL USART_transmit_T
	ret

print_false:
	RCALL USART_transmit_F
	RCALL USART_transmit_A
	RCALL USART_transmit_L
	RCALL USART_transmit_S
	RCALL USART_transmit_E

	ret

print_terminate:
	RCALL USART_transmit_T
	RCALL USART_transmit_E
	RCALL USART_transmit_R
	RCALL USART_transmit_M
	RCALL USART_transmit_I
	RCALL USART_transmit_N
	RCALL USART_transmit_A
	RCALL USART_transmit_T
	RCALL USART_transmit_E
	RCALL print_new_line

	ret
	
print_finish:
	RCALL USART_transmit_I
	RCALL USART_transmit_empty
	RCALL USART_transmit_A
	RCALL USART_transmit_M
	RCALL USART_transmit_empty

	RCALL USART_transmit_F
	RCALL USART_transmit_I
	RCALL USART_transmit_N
	RCALL USART_transmit_I
	RCALL USART_transmit_H

	RCALL USART_transmit_empty
	RCALL USART_transmit_L
	RCALL USART_transmit_O
	RCALL USART_transmit_O
	RCALL USART_transmit_P

	RCALL print_new_line


	ret 	

print_cont1:

	RCALL USART_transmit_I
	RCALL USART_transmit_empty
	RCALL USART_transmit_A
	RCALL USART_transmit_M
	RCALL USART_transmit_empty
	RCALL USART_transmit_A
	RCALL USART_transmit_T
	RCALL USART_transmit_empty



	RCALL USART_transmit_C
	RCALL USART_transmit_O
	RCALL USART_transmit_N
	RCALL USART_transmit_T
	RCALL USART_transmit_I
	RCALL USART_transmit_N
	RCALL USART_transmit_U
	RCALL USART_transmit_E
	RCALL print_new_line

	rjmp keep_up 

	
print_correct_msg:
	rcall print_correct
	rcall print_new_line
	ret

print_false_msg:
	rcall print_false
	rcall print_new_line
	ret


	

print_msg:
	RCALL print_hello 
	RCALL print_empty
	RCALL print_please
	RCALL print_empty
	RCALL print_enter
	RCALL print_empty
	RCALL print_code
	RCALL print_new_line
	ret

print_lost1:
	RCALL USART_transmit_S
	RCALL USART_transmit_A
	RCALL USART_transmit_D
	RCALL USART_transmit_L
	RCALL USART_transmit_L
	RCALL USART_transmit_Y

	RCALL USART_transmit_empty 
	RCALL USART_transmit_Y
	RCALL USART_transmit_O
	RCALL USART_transmit_U

	RCALL USART_transmit_empty
	RCALL USART_transmit_L
	RCALL USART_transmit_O
	RCALL USART_transmit_S
	RCALL USART_transmit_T

	RCALL print_new_line
	
	ret

print_win:
	RCALL USART_transmit_C
	RCALL USART_transmit_O
	RCALL USART_transmit_N
	RCALL USART_transmit_G
	RCALL USART_transmit_R
	RCALL USART_transmit_A
	RCALL USART_transmit_T
	RCALL USART_transmit_empty

	RCALL USART_transmit_Y
	RCALL USART_transmit_O
	RCALL USART_transmit_U
	RCALL USART_transmit_empty
	RCALL USART_transmit_W
	RCALL USART_transmit_I
	RCALL USART_transmit_N
	RCALL print_new_line

; subrouting responsible for turning on the LED
TURNON_LED:
	LDI PORTDEF, 0b00000010
	OUT PORTB, PORTDEF
	RET



;#################################################################################
; flag: add_correct is responsible for adding value to code_val is being called if the order of joystick command is correct  
add_correct:
	inc COUNTER1	
	subi code_val, -2
	rjmp finish ;; PAY ATTEMTION 
;flag: add_false is repsonsible for printing false to confirm that the order is not correct and return to finish flag
add_false:
	inc COUNTER1
	rcall print_false_msg
	rjmp finish
	

;###########################################################################################################
; subroutine WHIT is response for giving delay of couple second
; I made initial because I could not do something similar to the DEBOUNCE till now which 10.30 sunday. 
; I have to write the report I decided against taking off
WHIT:
	CLR R0
	SBI DDRB,5 
WHLUPE: 
	SBI  PINB,5         ;SET PORTB-BIT5
    RCALL WPAUSE        ;WAIT
    DEC R0
    BRNE WHLUPE        ;LOOP AROUND
    RET
WPAUSE:
	 PUSH R0             ;PAUSE TWEEN PULSES
WPLUPE: 
	DEC R0              ;IE DETERMINS FREQ
    BRNE WPLUPE
    POP R0
    RET	 		

PAUSE:
DELAY: 
	push A
    ldi A,8
DLUPE: 
	DEC R0
	BRNE DLUPE
	DEC R1
	BRNE DLUPE
	DEC A
	BRNE DLUPE
	POP A
    RET
    

;#####################################################################################################
			 
; this flag just said continue		
cont1:
	rjmp print_cont1
	keep_up: 
	rjmp poll_joysticks
; this flag terminate
terminate:
	;rcall print_lost1
	rcall print_terminate
	;rcall BEEPNOISE 
	rjmp DONE


;;###################################################################
;;###################################################################
;Beepnoise sets the buzzer high (at PortB, Pin 5) and then
;sits in a loop so that the buzzer is low enough frequency to be hearable to the
;human ear.

WASTETIME:
	CLR COUNTER3
CONTWASTETIME:
	NOP
	DEC COUNTER3
	BRNE CONTWASTETIME
		RET

BEEPNOISE:
	LDI PORTDEF, 0b00100000
	OUT	PORTB, PORTDEF
	;Wastetime is a counter that counts to 255 and then returns.
	RCALL WASTETIME
	;Once wastetime is finished, the buzzer is turned off 
	LDI PORTDEF, 0b11011111
	OUT	PORTB, PORTDEF
	;Wastetime is called again to make the period of the soundwave even lower
	RCALL WASTETIME
	;This whole thing is done 255 times to make the buzzer hearable.
	DEC COUNTER2
		BRNE BEEPNOISE
	RET
;###########################
; this block does the necessary steps to handle joystick command with respect the secret code
;#########################3

; case up check if the counter == 0 if so label the entry as correct code 
js_up:
	RCALL print_up
	;rcall debounce_up
	cpi COUNTER1, $0
	breq add_correct
	brne add_false

js_down:
	RCALL print_down
	;rcall debounce_down
	cpi COUNTER1, $1
	breq add_correct
	brne add_false

js_left:
	RCALL print_left
	;rcall debounce_left
	cpi COUNTER1, $2
	breq add_correct
	brne add_false
;###################

;###################
js_right:
	RCALL print_right
	;rcall debounce_right
	cpi COUNTER1, $3
	breq add_correct
	brne add_false
;###########################################################################

;###########################################################################
WIN_CODE:
	rcall print_win
	;rcall TURNON_LED ; you can call it when you connect the LED 
	rjmp terminate

;##############################################################################
;VARY IMPORTANT NOTE
; if you at flag test_passed I supposed to put "brne Lost" after "cpi code_val, $8" 
; but I kept on getting branch out of reach. 
;even when I add a call to a "print_lost" from "terminate" flag, kept on giving me out of reach error  
;##############################################################################


;LOST:
	;rcall print_lost
;	rcall BEEPNOISE
;	rcall Done
;	rjmp terminate


test_passed:
	cpi code_val , $8
		;brne LOST this gave me of reach error 
		brne terminate
		breq WIN_CODE
		;rcall print_lost
		;rjmp terminate 




;###########################################################################
; wait for the user to finish pressing and jump back to poll_joystick loop
;Equilvant to the debounce flag from disc2 
;###########################################################################
Joystick_not_pressed:
	rcall DELAY
	
	sbic PINB, 6
	rjmp poll_joysticks
		
	sbic PINB, 7
		rjmp poll_joysticks
		
	sbic PINE, 3
		rjmp poll_joysticks
		
	sbic PINE, 2
		rjmp poll_joysticks
		
		 
	rjmp joystick_not_pressed

;###############################################################################
;poll_joysticks is the main loop 
;getting the command from joysticks and call the apprioate subroutins and flags
; the logic breaks up as follow
; set counter keep track of entries
; 1-check up_js flag, if so, then jump up_js and there it will check counter1 == 0 if so it means the user clicked up in the first step which indicates the entry is correct. 
; if entry is correct then will add 2  to code_val = R19. the code_val keeps track of entries if an entry is the right sequnce, it will increment by 2 else no increment. 

; the same logic follow on the other entries. 
; the way I am telling whether code is correcct or not I just check_val == 8 which means all entries appeared in the right sequence.  
;  
;################################################################################
poll_joysticks:
	
	rcall DELAY


	SBIS PINB, 6
		RJMP Js_up
	
	SBIS PINB, 7
		RJMP js_down


	SBIS PINE, 2
		RJMP js_left


	SBIS PINE,3 
		RJMP js_right

	; if nothing on the joystick is pressed jump to Debounce state 
	rjmp Joystick_not_pressed

	 

;this flag help ensure the continuation of flow call print_finish used for debbuggin purposes
;
finish:
	rcall print_finish
	rcall WHIT
	
		
	rcall DELAY
	cpi COUNTER1, $4
	brne cont1
	breq test_passed
	
;####################################### 
; the block of is not used I just did wanna gamble and take it off 
;#######################################
PORT_A_INIT:
	LDI A, 0b00100010
	OUT DDRB, A
	LDI A, 0b10000000
	OUT PORTD, A
	ret



;#####################################################
;start: the main subroutine code start here
;#####################################################
START:
LDI TEMP, HIGH(RAMEND) ; Upper byte
OUT SPH,TEMP ; to stack pointer
LDI TEMP, LOW(RAMEND) ; Lower byte
OUT SPL,TEMP; to stack pointer

LDI A, HIGH(RAMEND) ; Upper byte
OUT SPH,A ; to stack pointer
LDI A, LOW(RAMEND) ; Lower byte
OUT SPL,A; to stack pointer

CLR R8

SER A   ; set 0xff
OUT	PORTB,A  ; initailize portB
OUT	PORTE,A ; initailize portE
;rcall PORT_A_INIT
RCALL USART_Init
rcall print_start
rcall print_msg

RCALL poll_joysticks



RCALL Done