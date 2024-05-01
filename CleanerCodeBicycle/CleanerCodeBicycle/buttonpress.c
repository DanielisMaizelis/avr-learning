#include "buttonpress.h"
#include <avr/io.h>

volatile unsigned char CurrentButtonState=0,PreviousButtonState=0;

void initButton(){
	DDRD &= ~(1<<DDD2);
	PORTD |= (1<<DDD2);
	PreviousButtonState = 0;
	CurrentButtonState = 0;
}

char buttonPressed(){
	PreviousButtonState = CurrentButtonState;
	CurrentButtonState = BUTTON_PRESSED;
	return ((PreviousButtonState==0) && (CurrentButtonState !=0))
}