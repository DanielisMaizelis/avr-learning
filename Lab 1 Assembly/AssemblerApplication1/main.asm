.include "m328Pdef.inc"


ldi r18, 0 
ldi r16,100 
ldi r17,16 
mul r16,r17



/*

.def COUNTER_16			   = R16
.def COUNTER_LIMIT_LOOP_17 = R17

.def SUM1_18 = R18
.def SUM2_19 = R19

.def MOV1_20 = R20
.def MOV2_21 = R21

.def COUNTER_LIMIT_IF_22 = R22
.def E = R19


loop: // Marking where we are in the memory

	// Iftwo Main Loop
	ldi COUNTER_16, 0
	ldi COUNTER_LIMIT_LOOP_17, 4

	ldi SUM1_18 = 1
	ldi SUM2_19 = 2

	ldi MOV1_20 = 3
	ldi MOV2_21 = 4

	ldi COUNTER_LIMIT_IF_22 = 1

	ldi E = R19

	/*
	// Summing
	ldi R18, 100
	ldi R19, 1


	// Moving
	ldi R20, 2
	ldi R21, 2

	// Multiplication
	ldi R22, 3
	ldi R23, 4

	// Ifone
	ldi R24, 2*/

	/*
	loopstart:
		inc COUNTER_16
		ifOne:
			cp  COUNTER_16, COUNTER_LIMIT_IF_22
			breq copy // A is less than B, go to the func "inside the loop"
		mul	 R,E
		push R17 
		pop	 R18
		ifTwo:
			cp	COUNTER_16, COUNTER_LIMIT_LOOP_17
			brlt continue // A is less than B, go to the func "inside the loop"
	rjmp loop


continue:
	rjmp loopstart

copy:
	mov MOV1_20, MOV2_21	// C will copy D C is 1
	add SUM1_18, SUM2_19    // C will be 5
	rjmp ifTwo
*/
/*
.equ LED_PORT = PORTD
.equ LED_PIN  = 5

setup:
    ldi r16	  1 << LED_PIN
	out DDRD, r16

start:
	// Turns on the LED
	ldi r16 (1 << LED_PIN)
	out LED_PORT, r16

	// Triggers the delay
	ldi r17, 200
	rjmp Delay

	add A, B     // A = 5, B = 3
    mul A, B	 // Multiplication goes to a different register 16-bit

	push A       // ??
	pop  B		 // ??

	rjmp start	 // Goes to the start:


Delay:
	dec r17
	ldi r18, 1
	*/