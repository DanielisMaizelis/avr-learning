.include "m328pdef.inc" ;this file name corresponds to processor name MIGHT give

;problems better to use include
;""
;add contents of two registers
LDI R16, 3 ; set R16 = 3
LDI R17, 10 ;set R17 = 10
LDI R18, 2 ; set R18 =2
MOV R2, R18 ; copy R18 to R2 MOV R1, R17; copy R17 to R1
START:
	ADD R1, R2 ;store sum of R1 and R2 to R1
	DEC R16 ;decrease R16 by 1
	BRNE start
	OUT PORTD, R1 ;store R1 in PORTD
	FOREVER:
	RjMP FOREVER; forever loop