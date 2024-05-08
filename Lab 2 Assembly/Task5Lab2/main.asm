.include "m328pdef.inc"
/*
// Task 2:
LDI r19, 45
LDI r18, 50
; Compares 2 values
CP  r18, r19
BRGE greater_than       ; Branches if the r19 >= r18
BRLT less_than_or_equal 

greater_than:
;when r19 <= r18 or r18>=r19
LDI r16, 0x02
; Sets the value for port B
OUT DDRB, r16
OUT PORTB, r16
RET ; Returns back to the the beginning of the program

less_than_or_equal:
;when r19 > r18 or r18 < r19
LDI r16, 0x01
; Sets the value for port B
OUT DDRB, r16
OUT PORTB, r16


// Task 3:
// Task 3.1
; 2 integer values:
ldi  r18, 2
ldi  r16, 2

ldi  r19, 0 ; Register that is incremented
ldi  r17, 1 ; Register that keeps bit shifted value

add r18,r16 ; Adds registers and stores in r18

loop:
cp r19, r18  ; Compares 2 registers
brlt loopin  ; If the incremented value is less than r18, branch
OUT DDRB , r17
OUT PORTB, r17
rjmp loop

loopin:
lsl r17   ; bit-shift to left
inc r19	  ; Increment a value
rjmp loop ; Jump back to loop


// Task 3.2
; 2 Integer values
ldi  r18, 3
ldi  r16, 2

ldi  r19, 0 ; Register that is incremented
ldi  r17, 1 ; Register that keeps bit shifted value

mul r18,r16 ; Adds registers and stores in r18

loop:
cp r19, r0  ; Compares 2 registers
brlt loopin  ; If the incremented value is less than r18, branch
OUT DDRB , r17
OUT PORTB, r17
rjmp loop

loopin:
lsl r17   ; bit-shift to left
inc r19	  ; Increment a value
rjmp loop ; Jump back to loop


// Task 3.3
; 2 integer values:
ldi  r18, 3
ldi  r16, 2

ldi  r19, 0 ; Register that is incremented
ldi  r17, 1 ; Register that keeps bit shifted value

sub r18,r16 ; Adds registers and stores in r18

loop:
cp r19, r18  ; Compares 2 registers
brlt loopin  ; If the incremented value is less than r18, branch
OUT DDRB , r17
OUT PORTB, r17
rjmp loop

loopin:
lsl r17   ; bit-shift to left
inc r19	  ; Increment a value
rjmp loop ; Jump back to loop

// Task 4:
; Register that keeps the biggest value
ldi r19, 0

; 10 registers that contain integer values
ldi r16, 1
ldi r17, 2
ldi r18, 7 
ldi r20, 1
ldi r21, 1
ldi r22, 3
ldi r23, 1
ldi r24, 1
ldi r25, 1
ldi r26, 1

; Register for incrementing (in a loop)
ldi r27, 0

; Register that keeps the bit-shifted value
ldi r30, 1

loop:
	ld r19, x ; Loads value from memory

	; Compares 10 integer values:
	; If the integer value is bigger than r19, it branches to a condition (c1 to c10)
	cp r19,r16
	brlt c1

	cp r19,r17
	brlt c2

	cp r19,r18
	brlt c3

	cp r19,r20
	brlt c4

	cp r19,r21
	brlt c5

	cp r19,r22
	brlt c6

	cp r19,r23
	brlt c7

	cp r19,r24
	brlt c8

	cp r19,r25
	brlt c9

	cp r19,r26
	brlt c10
	
	; r19 has the max value
	cp r27, r19
	brlt loopin ; branches if the max value (r19) is bigger than r27
	OUT DDRB , r30 ; Activates the pins based on the bit-shifted value
	OUT PORTB, r30 ; Sets pins to high based on the bit-shited value
	rjmp loop


loopin:
	lsl r30 ; But shifts value to the left for register 30
	inc r27 ; increments the register 27
	rjmp loop ; goes back to the start

; Inside each condition (c1 to c10), r19 moves the value of the register that was previously compared
; r19 values are tsored in the memory
; then it jumps back to the beginning of the loop
c1:
	mov r19, r16
	st x, r19
	rjmp loop

c2:
	mov r19, r17
	st x, r19
	rjmp loop

c3:
	mov r19, r18
	st x, r19
	rjmp loop

c4:
	mov r19, r20
	st x, r19
	rjmp loop
c5:
	mov r19, r21
	st x, r19
	rjmp loop
c6:
	mov r19, r22
	st x, r19
	rjmp loop
c7:
	mov r19, r23
	st x, r19
	rjmp loop
c8:
	mov r19, r24
	st x, r19
	rjmp loop
c9:
	mov r19, r25
	st x, r19
	rjmp loop
c10:
	mov r19, r26
	st x, r19
	rjmp loop

	*/
// Task 5:
.def  lowValue  = r24		; register value low
.def  highValue = r25		; register value high


; ncycles = 2 + 4 * (clockCount - 1) + 3
; ncycles = 2+ 4*(16000-1) + 3
; ncycles = 4*16000+1
.equ  iVal 	  = 64001	    ; inner loop value 16000 - 1

ldi	  lowValue, LOW(iVal)  	; init of low value 
ldi	  highValue, HIGH(iVal) ; init of high value

loop:	
	sbiw	lowValue, 1		; decrement  the lower value register together with the high value register
	brne	loop			; branch if lowValue and highValue is 0
	ret				        ; return back to the beginning
