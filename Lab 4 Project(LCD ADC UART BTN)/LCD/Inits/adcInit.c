#include "../include/main.h"

void adcInit()
{
	DDRC   &= 0x00;					  // Set the pins for analog as input
	PORTC  &= 0x00;			          // Set the pins for analog as input
	// Enable ADC, ADC Interrupt
	ADCSRA |= (1 << ADEN) | (1 << ADIE)| (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
	ADMUX  |= 1 << REFS0;			  // Set reference voltage to AVCC
	// Start conversion and interrupts
	ADCSRA |= (1 << ADSC)|(1<< ADIE);
}
