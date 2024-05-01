
.include "m328pdef.inc" ; this file must correspond to the processor to be used


/*
.list
tester :
LDI R17 , 16 ; set R17 =16 (0 x10 )
LDI R18 , 32 ; set R18 =32 (0 x20 )
MOV R1 , R17 ; set R1 = R17
MOV R2 , R18 ; set R2 = R18
ADD R1 , R2 ;R1 = R1+R2
CLR R27 ; clear higher byte of memory index register (=00)
LDI R26 , 80 ; set lower index register to destination memory address
ST x+ , R19 ; store the sum in memory pointed by pair R27: R26
STS 128 , R1 ; store the sum (R1) at a pre - specified address (128)
LDI R17 , 127 ;( Refer to the comments above )
LDI R18 , 126
ADD R17 , R18
INC R26 ; increment the index so that it points to the next memory location
ST x+ , R17 ; store the sum
LDI R19 , 254 ;( Refer to the comments above )
LDI R20 , 2
ADD R19 , R20
INC R26 ; increment the index so th

*/



