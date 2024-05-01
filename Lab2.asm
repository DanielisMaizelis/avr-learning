.include "m328pdef.inc" ; this file must correspond to the processor to be used





ldi r15, 0 
ldi r0, 16000


/*

ldi  r15, 1
ldi  r16, 2
ldi  r14, 0
ldi  r17, 0

add r15,r16 // 3

loop:
cp r15, r14
brlt loopin
rjmp loop

loopin:
lsl r17 
inc r14
rjmp loop


*/