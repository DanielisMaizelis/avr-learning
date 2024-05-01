#include "button.h"
unsigned char CurrentButtonState=0,PreviousButtonState=0;
#define BUTTON_PRESSED (0 == (PIND & (1<<PORTD2)))

void Button_Init(void)
{
	DDRD &= ~(1<<DDD2);
	PORTD |= (1<<DDD2);
}

uint8_t ButtonPresedOnce(void)
{
	
	
}