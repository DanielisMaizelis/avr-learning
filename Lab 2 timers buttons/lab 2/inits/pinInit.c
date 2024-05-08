#include "../main.h"


void pinSetup(void) // Led's
{
	// Pins for Leds and button
	DDRB  |= (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB5);
	
	// Pins for the traffic light
	DDRD  |= (1<<PORTD7)|(1<<PORTD6)|(1<<PORTD5);
	
	// Button pull-up setup polling
	DDRD  &= ~(1<<PORTD2); // 
	PORTD |= (1<<PORTD2);
}
